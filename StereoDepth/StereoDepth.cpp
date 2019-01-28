#include "StereoDepth.h"

#include "opencv2/opencv.hpp"

//#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <array>
#include <string>

//Function prototipation
void fillOcclusion(cv::Mat& src, int invalidvalue, bool isInv=false);

using namespace cv;
using namespace std;

namespace sd {


StereoDepth::StereoDepth()
{
}


void StereoDepth::loadCameraParams(const std::string& directory) throw(std::exception)
{

    //Undistort points
    Mat M1,M2,P1,P2,D1,D2,R1,R2,Q;

    FileStorage fs;
    if( fs.open(directory + "/M1.xml", FileStorage::READ) ) {
        fs["M1"] >> M1;
        fs.release();

        if (fs.open(directory + "/M2.xml", FileStorage::READ) ) {
            fs["M2"] >> M2;
            fs.release();
            if( fs.open(directory + "/P1.xml", FileStorage::READ) ) {
                fs["P1"] >> P1;
                fs.release();

                if (fs.open(directory + "/P2.xml", FileStorage::READ) ) {
                    fs["P2"] >> P2;
                    fs.release();

                    if( fs.open(directory + "/D1.xml", FileStorage::READ) ) {
                        fs["D1"] >> D1;
                        fs.release();

                        if( fs.open(directory + "/D2.xml", FileStorage::READ) ) {
                            fs["D2"] >> D2;
                            fs.release();

                            if ( fs.open(directory + "/R1.xml", FileStorage::READ) ) {
                                fs["R1"] >> R1;
                                fs.release();

                                if ( fs.open(directory + "/R2.xml", FileStorage::READ) ) {
                                    fs["R2"] >> R2;
                                    fs.release();

                                    if ( fs.open(directory + "/Q.xml", FileStorage::READ) ) {
                                        fs["Q"] >> Q;
                                        fs.release();

                                        //Now all files are open
                                        Matx44d _Q;
                                        Q.convertTo(_Q,_Q.type);
                                        std::copy(_Q.val, _Q.val + _Q.cols*_Q.rows, &this->Q[0][0]);

                                        Matx34d _P;
                                        P1.convertTo(_P,_P.type);
                                        std::copy(_P.val, _P.val + _P.cols*_P.rows, &this->P1[0][0]);

                                        P2.convertTo(_P,_P.type);
                                        std::copy(_P.val, _P.val + _P.cols*_P.rows, &this->P2[0][0]);

                                        Matx33d _M;
                                        M1.convertTo(_M,_M.type);
                                        std::copy(_M.val, _M.val + _M.cols*_M.rows, &this->M1[0][0]);

                                        M2.convertTo(_M,_M.type);
                                        std::copy(_M.val, _M.val + _M.cols*_M.rows, &this->M2[0][0]);

                                        R1.convertTo(_M,_M.type);
                                        std::copy(_M.val, _M.val + _M.cols*_M.rows, &this->R1[0][0]);

                                        R2.convertTo(_M,_M.type);
                                        std::copy(_M.val, _M.val + _M.cols*_M.rows, &this->R2[0][0]);

                                        Matx<double, 1, 5> _V;
                                        D1.convertTo(_V,_V.type);
                                        std::copy(_V.val, _V.val + _V.cols*_V.rows, &this->D1[0]);

                                        D2.convertTo(_V,_V.type);
                                        std::copy(_V.val, _V.val + _V.cols*_V.rows, &this->D2[0]);

                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //If we arrived here, there is a problem...
        throw std::domain_error("Problem while trying to open camera parameters from " + directory );

    }

}

void StereoDepth::process(const ip::Image &left, const ip::Image &right, ip::CDImage& colordepth, std::vector<ip::Point3<float> >& points)
{

    //TODO: check if left and right have the same sizes
    Size imgSize = left.nativeImage<Mat>().size();
    int imgType = left.nativeImage<Mat>().type();
    Mat prev(imgSize,imgType), next(imgSize,imgType);


    //Correct Images - undistort and rectify
    Mat mx1, my1, mx2, my2;
    initUndistortRectifyMap(Matx33d(&M1[0][0]), Matx<double,1,5>(&D1[0]),Matx33d(&R1[0][0]),Matx34d(&P1[0][0]), imgSize, CV_32F, mx1, my1);
    initUndistortRectifyMap(Matx33d(&M2[0][0]), Matx<double,1,5>(&D2[0]),Matx33d(&R2[0][0]),Matx34d(&P2[0][0]), imgSize, CV_32F, mx2, my2);

    cv::remap(left.nativeImage<Mat>(), prev, mx1, my1, CV_INTER_CUBIC);
    cv::remap(right.nativeImage<Mat>(), next, mx2, my2, CV_INTER_CUBIC);

    //Defines SGBM disparity extractor
    /*
     * int minDisparity, int numDisparities, int SADWindowSize,
               int P1=0, int P2=0, int disp12MaxDiff=0,
               int preFilterCap=0, int uniquenessRatio=0,
               int speckleWindowSize=0, int speckleRange=0,
               bool fullDP=false
       1,16*2,3,200,255,1,0,0,0,0,true
     */

    int minDisparity=0;
    int numDisparities=16*8;
    int SADWindowSize=5;
    int p1=300; //Penalty for 1-difference in neighbor-pixel disparity
    int p2=400; //Penalty for >1-difference in neighbor-pixel disparity
    int disp12MaxDiff=0;
    int prefilterCap=0;
    int uniquenessRatio=0;
    int speckleWindowSize=0;
    int speckleRange=0;
    bool fullDP = true;

    StereoSGBM sgbm(minDisparity, numDisparities, SADWindowSize,p1,p2,
                    disp12MaxDiff, prefilterCap, uniquenessRatio,
                    speckleWindowSize, speckleRange, fullDP);

    Mat disp(imgSize,CV_16S);
    sgbm(prev,next,disp);
    fillOcclusion(disp,120);

    if(1) {
        printf("Disparity image type:%d ", disp.type());
        imshow("Disparity",disp);
        waitKey();
        destroyWindow("Disparity");
    }

    //Finally, find the depth (Z) in the baseline unity
    //we know that W = disp/baseline + correction

    double baseline_inv = Q[3][2];
    double correction = Q[3][3];

    Mat w;
    disp.convertTo(w,CV_32F,baseline_inv,correction);

    //Wrappers
    points.resize(w.size().area());
    Mat res_points(w.size(),CV_32FC3,&points[0][0]);
    std::vector<Mat> _pts(3);
    Mat& x = _pts[0];
    Mat& y = _pts[1];
    Mat& depth = _pts[2];

    //Finally, depth = f/W
    float focaldist = Q[2][3];
    depth = focaldist/w;


    if(1) {
        Mat normal;
        normalize(depth,normal,0,255,NORM_MINMAX,CV_8UC1);
        imshow("Depth",normal);
        waitKey();
        destroyWindow("Depth");
    }

    colordepth.color().nativeImage<Mat>() = prev;
    colordepth.depth().nativeImage<Mat>() = depth;

    //Process point position
    std::vector<float> buf(w.size().width);
    std::vector<float> xbuf(w.size().area());
    std::vector<float> ybuf(w.size().area());

    float xc = -Q[0][3], yc = -Q[1][3];

    //Fill xbuffer
    int counter = 0;
    for(float& a : buf) { a = (float)counter++ - xc; }
    //xbuf.end() = xbuf.begin() + height*buf.size()
    for(auto it = xbuf.begin(); it != xbuf.end(); it += buf.size()) {
        std::copy(buf.begin(), buf.end(), it);
    }

    //Fill ybuffer
    counter=0;
    for(auto it = ybuf.begin(); it != ybuf.end(); it += w.size().width) {
        std::fill(it, it+w.size().width, counter++ - yc);
    }

    x = Mat(w.size(),CV_32F,&xbuf[0])/w;
    y = Mat(w.size(),CV_32F,&ybuf[0])/w;
    cv::merge(_pts,res_points);

    //Debug
    if(0) {
        cv::split(res_points,_pts);
        for(Mat& img : _pts) {
            Mat show;
            cv::normalize(img,show,0,255,cv::NORM_MINMAX,CV_8U);
            imshow("Debug",show);
            waitKey();
        }
        destroyWindow("Debug");

    }

}

}
