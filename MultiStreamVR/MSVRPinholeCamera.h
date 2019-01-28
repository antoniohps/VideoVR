#ifndef MSVR_MSVRPINHOLECAMERA_H
#define MSVR_MSVRPINHOLECAMERA_H

#include "MSVRCamera.h"

namespace msvr {

class MSVRPinholeCamera : public MSVRCamera
{
public:
    MSVRPinholeCamera(double focal, int width, int height) :
        MSVRCamera(width,height), m_focal(focal)  {}

    ///Project 3d points into camera image surface
    virtual std::vector<ip::Point2<float> > projectPoints(const std::vector<ip::Point3<float> > &points3D) const;
private:
    double m_focal;
};

} // namespace msvr

#endif // MSVR_MSVRPINHOLECAMERA_H
