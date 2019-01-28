#include "Image.h"

#include <opencv2/highgui/highgui.hpp>


#define IMAGEIMPL reinterpret_cast<cv::Mat*>(_imageImpl)

namespace ip {

Image::Image() : _type(Type::IMG_OPENCV_TYPE)
{
    _imageImpl = new cv::Mat(0,0,CV_8UC3);
}

Image::Image(const std::string& file) : _type(Type::IMG_OPENCV_TYPE)
{
    _imageImpl = new cv::Mat( cv::imread(file) );
}

Image::~Image()
{
    delete reinterpret_cast<cv::Mat*>(_imageImpl);
}

template <> cv::Mat& Image::nativeImage<cv::Mat>()
{
    return *IMAGEIMPL;
}

template <> const cv::Mat& Image::nativeImage<cv::Mat>() const
{
    return *IMAGEIMPL;
}

Image Image::clone() const
{
    Image newImg;
    IMAGEIMPL->copyTo(newImg.nativeImage<cv::Mat>());
    return newImg;
}

void Image::resize(int width, int height)
{
    IMAGEIMPL->create(height, width,IMAGEIMPL->type());
}

template <typename T, typename C> void __drawPoints(
        cv::Mat& image,
        const std::vector<Point2<T> >& points,
        const cv::Mat& colors)
{
    auto pt_it = points.begin();
    auto cl_it = colors.begin<C>();

    for(; pt_it != points.end() && cl_it != colors.end<C>(); ++pt_it, ++cl_it) {

        auto x = pt_it->x();
        auto y = pt_it->y();

        if(x >= 0.0 && x < ((double)image.cols-0.9) && y>=0 && y < ((double)image.rows-0.9)) {

            //TODO: cause a wider spot in image
            image.at<C>(::round(y),::round(x)) = *cl_it;
        }
    }
}


template <> void Image::drawPoints<float>(
        const std::vector<Point2<float> > &points,
        const ip::Image &color)
{

    const cv::Mat& colors = color.nativeImage<cv::Mat>();
    cv::Mat& theImg = this->nativeImage<cv::Mat>();

    if(colors.type() == CV_8UC3 && theImg.type() == CV_8UC3) {
        __drawPoints<float,std::array<uchar,3> >(theImg,points,colors);
    }

}


void Image::loadFromFile(const std::string &file)
{
    *IMAGEIMPL = cv::imread(file);
}

///////////////////////////////
template <typename T> void colorAssign (cv::Mat& img, const Point3<T>& color)
{
    if(img.channels() == 1) img.setTo(cv::Scalar(color.x()));
    else if(img.channels() == 3) img.setTo(cv::Scalar(color.x(),color.y(),color.z()));
}

template <> Image& Image::operator=(const Point3<unsigned char> &color)
{
    colorAssign(*IMAGEIMPL,color);
    return *this;
}

template <> Image& Image::operator=(const Point3<int> &color)
{
    colorAssign(*IMAGEIMPL,color);
    return *this;
}


}

