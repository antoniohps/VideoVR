#ifndef MSVRIMAGE_H
#define MSVRIMAGE_H

namespace msvr {

//! Wrapper for an image in a base API format
class MSVRImage
{
public:

    enum Type {
        IMG_NO_TYPE,
        IMG_OPENCV_TYPE
    };

    MSVRImage();

private:

    Type _type;


};

}
#endif // MSVRIMAGE_H
