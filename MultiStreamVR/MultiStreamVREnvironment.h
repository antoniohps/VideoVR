#ifndef MULTISTREAMVRENVIRONMENT_H
#define MULTISTREAMVRENVIRONMENT_H

#include "MSVRStream.h"
#include "MSVRCamera.h"

#include <memory>
#include <unordered_set>
#include <unordered_map>

namespace msvr {

class MultiStreamVREnvironment
{

    //! Container of pointers to streams
    typedef std::unordered_set< std::shared_ptr<MSVRStream> > stream_container;
    typedef stream_container::iterator stream_iterator;
    typedef stream_container::const_iterator stream_const_iterator;

    //! Container of point matches
    typedef std::unordered_map<ip::Point2<float>,ip::Point2<float> > point_match_map;

public:
    MultiStreamVREnvironment();

    /// Add color-depth stream
    void addStream(std::shared_ptr<MSVRStream> stream);

    /// Remove color-depth stream
    void removeStream(std::shared_ptr<MSVRStream> stream);

    ///Try to match a new stream with one of the previous streams
    /// @returns the mapping of matched points
    point_match_map matchStream(MSVRStream& stream, stream_const_iterator& previous) const;

    ///Show point cloud
    void showPoints(const MSVRCamera& camera, ip::Image& view);

private:

    stream_container m_streams;

};

}

#endif // MULTISTREAMVRENVIRONMENT_H
