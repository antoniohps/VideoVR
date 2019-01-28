#ifndef MSVR_MSVRSTEREOIMAGE_H
#define MSVR_MSVRSTEREOIMAGE_H

#include "MSVRStream.h"
#include "StereoDepth.h"

#include <string>

namespace msvr {

class MSVRStereoImage : public msvr::MSVRStream
{
public:
    //There can't be a default constructor
    MSVRStereoImage() = delete;

    /// Constructor taking the calibration directory
    MSVRStereoImage(const std::string& calibDirectory);

    /// Destructor
    virtual ~MSVRStereoImage();

    /// Process stereoscopic image
    void process(const std::string& leftFile,  const std::string& rightFile);

    /// Return the next available Color-Depth image
    virtual const ip::CDImage& nextImage();

    /// Return the next available point cloud image
    virtual const std::vector<ip::Point3<float> >& nextPoints();

private:
    bool m_hasImage;

    std::string m_leftFile;
    std::string m_rightFile;
    ip::CDImage m_colordepth;

    std::vector<ip::Point3<float> > m_points;

    double m_imgCenterX, m_imgCenterY;

    sd::StereoDepth m_processor;

};

} // namespace msvr

#endif // MSVR_MSVRSTEREOIMAGE_H
