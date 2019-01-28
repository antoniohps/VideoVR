#include "MSVRStereoImage.h"

using namespace ip;
using namespace sd;

namespace msvr {

MSVRStereoImage::MSVRStereoImage(const std::string &calibDirectory) :
    m_hasImage(false)
{
    m_processor.loadCameraParams(calibDirectory);
}

MSVRStereoImage::~MSVRStereoImage()
{

}

void MSVRStereoImage::process(const std::string &leftFile, const std::string &rightFile)
{
    m_leftFile = leftFile;
    m_rightFile = rightFile;

    Image left(leftFile);
    Image right(rightFile);

    this->m_processor.process(left,right,m_colordepth, m_points);

    m_hasImage = true;

}

const ip::CDImage &MSVRStereoImage::nextImage()
{
    return m_colordepth;
}

const std::vector<ip::Point3<float> >& MSVRStereoImage::nextPoints()
{
    return m_points;
}

} // namespace msvr
