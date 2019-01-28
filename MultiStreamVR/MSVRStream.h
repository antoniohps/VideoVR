#ifndef MSVRSTREAM_H
#define MSVRSTREAM_H

#include "CDImage.h"

#include <vector>

namespace msvr {

class MSVRStream
{
public:
    MSVRStream();

    /// Return the next available Color-Depth image
    virtual const ip::CDImage& nextImage() = 0;

    /// Return the 3D points
    virtual const std::vector<ip::Point3<float> >& nextPoints() = 0;

};

}
#endif // MSVRSTREAM_H
