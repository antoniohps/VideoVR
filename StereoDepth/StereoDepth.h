#ifndef STEREODEPTH_H
#define STEREODEPTH_H

#include "Image.h"
#include "CDImage.h"

#include <array>
#include <stdexcept>

namespace sd {

template <typename T, std::size_t M, std::size_t N> struct MatMN :
        public std::array<std::array<T,N>,M>
{};

template <typename T, std::size_t N> struct vecN :
        public std::array<T,N>
{};


class StereoDepth
{

public:
    StereoDepth();

    void loadCameraParams(const std::string &directory) throw(std::exception);

    void process(const ip::Image& left, const ip::Image& right, ip::CDImage& colordepth, std::vector<ip::Point3<float> >& points );

private:

    MatMN<double,4,4> Q; //Disparity to depth matrix
    MatMN<double,3,4> P1, P2; //Camera 1 and 2 projection matrices
    MatMN<double,3,3> M1,M2,R1,R2;
    vecN<double,5> D1, D2; //Distortion coefficients (cameras 1 and 2)


};


}

#endif // STEREODEPTH_H
