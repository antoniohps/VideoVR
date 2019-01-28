#ifndef IP_MSVRIMAGE_H
#define IP_MSVRIMAGE_H

#include "apiconfig.hpp"

#include <vector>

#include <array>
#include <string>
#include <stdexcept>

namespace ip {

//! Wraper for a 2D point
template <typename T> struct Point2 :
        public std::array<T,2>
{
    Point2() : std::array<T,2>({0,0}) { }
    Point2(const T& _x, const T& _y) :
        std::array<T,2>({_x,_y}) { }

    T& x() { return (*this)[0]; }
    const T& x() const { return (*this)[0]; }
    T& y() { return (*this)[1]; }
    const T& y() const { return (*this)[1]; }
};

//! Wraper for a 3D point
template <typename T> struct Point3 :
        public std::array<T,3>
{
    Point3() : std::array<T,3>({0,0,0}) {}
    Point3(const T& _x, const T& _y, const T& _z) :
        std::array<T,3>({_x,_y,_z}) { }

    T& x() { return (*this)[0]; }
    const T& x() const { return (*this)[0]; }
    T& y() { return (*this)[1]; }
    const T& y() const { return (*this)[1]; }
    T& z() { return (*this)[2]; }
    const T& z() const { return (*this)[2]; }
};


//! Wrapper for an image in a base API format
class Image
{
public:

    /// Indicates the undercovered API used
    enum Type {
        IMG_NO_TYPE,
        IMG_OPENCV_TYPE
    };

    /// Constructor
    Image();
    ///Copy constructor
    Image(const Image& img) : Image(img.clone()) { }
    ///Copy constructor with move semantics
    Image(Image&& img) : Image() { (*this) = std::move(img); }
    /// Constructor from a file
    Image(const std::string& file);
    ///Destructor
    ~Image();

    /// Resize image
    void resize(int width, int height);

    /// Create a deep copy of the image
    Image clone() const;

    /// Value assignment operator
    Image& operator=(const Image& image) {
        return (*this)=image.clone();
    }

    /// Value assignment operator for anonymous values
    Image& operator=(Image&& image) {
        if(image._type == this->_type) {
            std::swap(this->_imageImpl, image._imageImpl);
            return *this;
        } else throw std::logic_error("Cannot assign image of different type");
    }

    /// Value assignment operator for pixel value
    template <typename T> Image& operator=(const ip::Point3<T>& color);

    /// Draw points to the image
    template <typename T> void drawPoints(
            const std::vector<Point2<T> >& points,
            const Image& color);

    ///Loads image from file
    void loadFromFile(const std::string& file);

    ///Get the image type
    Type type() const { return _type; }

    ///Get reference to the API image implementation
    template<class T> T& nativeImage();
    ///Get constant reference to the API image implementation
    template<class T> const T& nativeImage() const;

private:

    Type _type;
    void* _imageImpl;
};

}
#endif // IP_MSVRIMAGE_H
