#include "MSVRCamera.h"

#include "opencv2/calib3d/calib3d.hpp"
namespace msvr {

MSVRCamera::MSVRCamera(int width, int height) :
    m_pos(0,0,0),
    m_att(0,0,0),
    m_width(width),
    m_height(height)
{
}

MSVRCamera::~MSVRCamera()
{

}

void MSVRCamera::moveUp(double dist)
{
    cv::Matx33d Rot;
    cv::Rodrigues(cv::Vec3d(&rodrigues()[0]),Rot);
    //Project vector (0,-dist,0) back to global coordinates
    //Y points down
    cv::Vec3d t = Rot.t()*cv::Vec3d(0, -dist, 0);
    m_pos[0] += t(0); m_pos[1] += t(1); m_pos[2] += t(2);
}

void MSVRCamera::moveLeft(double dist) {

    cv::Matx33d Rot;
    cv::Rodrigues(cv::Vec3d(&rodrigues()[0]),Rot);
    //Project vector (-dist,0,0) back to global coordinates
    cv::Vec3d t = Rot.t()*cv::Vec3d(-dist,0,0);
    m_pos[0] += t(0); m_pos[1] += t(1); m_pos[2] += t(2);
}

void MSVRCamera::moveForth(double dist) {

    cv::Matx33d Rot;
    cv::Rodrigues(cv::Vec3d(&rodrigues()[0]),Rot);
    //Project vector (0,0,dist) back to global coordinates
    cv::Vec3d t = Rot.t()*cv::Vec3d(0,0,dist);
    m_pos[0] += t(0); m_pos[1] += t(1); m_pos[2] += t(2);
}

void MSVRCamera::turnUp(double angle)
{
    assert(angle > -CV_PI/2 && angle < CV_PI/2);
    double tan_delta_psi =  ::tan(angle)*::cos(theta());
    double tan_delta_phi =  ::tan(angle)*::sin(theta());
    setPsi(psi() + ::atan(tan_delta_psi));
    setPhi(phi() + ::atan(tan_delta_phi));
}

void MSVRCamera::turnLeft(double angle)
{
    assert(angle > -CV_PI/2 && angle < CV_PI/2);
    double tan_delta_psi =  ::tan(angle)*::sin(theta());
    double tan_delta_phi = -::tan(angle)*::cos(theta());
    setPsi(psi() + ::atan(tan_delta_psi));
    setPhi(phi() + ::atan(tan_delta_phi));
}

void MSVRCamera::roll(double angle)
{
    setTheta(theta() + angle);
}

ip::Point3<double> MSVRCamera::rodrigues() const
{
    cv::Matx33d RotY(cos(phi()),0.0, -sin(phi()),
                     0.0       ,1.0,         0.0,
                     sin(phi()),0.0, cos(phi()));

    cv::Matx33d RotX(1.0, 0.0, 0.0,
                     0.0, cos(psi()),sin(psi()),
                     0.0, -sin(psi()), cos(psi()));

    cv::Matx33d RotZ(cos(theta()), sin(theta()), 0.0,
                     -sin(theta()), cos(theta()), 0.0,
                              0.0,          0.0, 1.0);

    cv::Vec3d rod;
    cv::Rodrigues(RotZ*RotY*RotX,rod);

    return ip::Point3<double>(rod(0),rod(1),rod(2));

}


} // namespace msvr
