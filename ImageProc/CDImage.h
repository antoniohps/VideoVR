#ifndef MSVR_MSVRCDIMAGE_H
#define MSVR_MSVRCDIMAGE_H

#include "MSVRImage.h"

namespace msvr {
//! Wrapper for color and depth information using a base API format
class MSVRCDImage
{
public:
    MSVRCDImage();

private:
    MSVRImage _color;
    MSVRImage _depth;
};




} // namespace msvr

#endif // MSVR_MSVRCDIMAGE_H
