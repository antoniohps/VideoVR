#include "MSVRPinholeCamera.h"

#include "opencv2/calib3d/calib3d.hpp"

namespace msvr {

std::vector<ip::Point2<float> > MSVRPinholeCamera::projectPoints(const std::vector<ip::Point3<float> >& points3D) const
{
    std::vector<cv::Point2f> imgPoints;

    //1. Find rotation matrix
    cv::Matx33d R;
    cv::Rodrigues(cv::Vec3d(&this->rodrigues()[0]),R);

    //2. Find the R-transformed translation vector
    cv::Vec3d t = R*cv::Vec3d(-m_pos[0],-m_pos[1],-m_pos[2]);

    //Find the camera instrinsics matrix
    cv::Matx33d M (m_focal, 0.0, m_width/2,
                   0.0, m_focal, m_height/2,
                   0.0,     0.0,       1.0);

    cv::projectPoints(
                cv::Mat(points3D.size(),3,CV_32F,const_cast<float*>(&points3D[0][0])),
                R, t, M, cv::noArray(), imgPoints
            );

    return *reinterpret_cast<std::vector<ip::Point2<float> >*>(&imgPoints);
}

} // namespace msvr
