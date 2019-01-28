#include "MultiStreamVREnvironment.h"

#include "opencv2/calib3d/calib3d.hpp"

namespace msvr {


MultiStreamVREnvironment::MultiStreamVREnvironment()
{
}

void MultiStreamVREnvironment::addStream(std::shared_ptr<MSVRStream> stream)
{
    m_streams.insert(stream);
}

void MultiStreamVREnvironment::removeStream(std::shared_ptr<MSVRStream> stream)
{
    m_streams.erase(stream);
}

void MultiStreamVREnvironment::showPoints(const MSVRCamera &camera, ip::Image &view)
{
    //Prepare output image
    view.resize(camera.imageWidth(),camera.imageHeight());
    view = ip::Point3<unsigned char>(0,0,0);

    //For each stream in the envionment
    for(auto& stream : this->m_streams) {

        //2. Project stream points into image
        auto projected = camera.projectPoints(stream->nextPoints());

        view.drawPoints(projected,stream->nextImage().color());
    }
}


}
