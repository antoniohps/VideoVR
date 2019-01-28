#ifndef MSVR_MSVRCDIMAGE_H
#define MSVR_MSVRCDIMAGE_H

#include "Image.h"

namespace ip {
//! Wrapper for color and depth information using a base API format
class CDImage
{
public:
    CDImage();

    void setColorImage(const Image& color) {
        _color = color;
    }

    void setColorImage(Image&& color) {
        _color = std::move(color);
    }

    void setDepthImage(const Image& depth) {
        _depth = depth;
    }

    void setDepthImage(Image&& depth) {
        _depth = std::move(depth);
    }

    const Image& color() const { return _color; }
    Image& color() { return _color; }
    const Image& depth() const { return _depth; }
    Image& depth() { return _depth; }

private:
    Image _color;
    Image _depth;
};


} // namespace msvr

#endif // MSVR_MSVRCDIMAGE_H
