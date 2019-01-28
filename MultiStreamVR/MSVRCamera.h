#ifndef MSVR_MSRVCAMERA_H
#define MSVR_MSRVCAMERA_H

#include "Image.h"

#include <array>
#include <vector>
#include <cmath>

namespace msvr {

class MSVRCamera
{
public:
    MSVRCamera(int width, int height);
    virtual ~MSVRCamera();

    ///Image height
    int imageHeight() const { return m_height; }

    ///Image width
    int imageWidth() const { return m_width; }

    ///Project 3d points into camera image surface
    virtual std::vector<ip::Point2<float> > projectPoints(const std::vector<ip::Point3<float> >& points3D) const = 0;

    ///Set camera position x-coordinate
    void setX(double x) { m_pos[0] = x; }
    ///Set camera position y-coordinate
    void setY(double y) { m_pos[1] = y; }
    ///Set camera position z-coordinate
    void setZ(double z) { m_pos[2] = z; }

    ///Get camera position x-coordinate
    double x() const {return m_pos[0]; }
    ///Get camera position y-coordinate
    double y() const {return m_pos[1];}
    ///Get camera position z-coordinate
    double z() const {return m_pos[2];}

    ///Get camera psi angle (in radians)
    double psi() const { return m_att[0]; }
    ///Get camera phi angle (in radians)
    double phi() const { return m_att[1]; }
    ///Get camera theta angle (in radians)
    double theta() const { return m_att[2]; }

    ///Set camera psi angle (in radians)
    void setPsi(double psi) { m_att[0] = std::max(-3.141592/2.0, std::min(3.141592,psi)); }
    ///Set camera phi angle (in radians)
    void setPhi(double phi) { m_att[1] = ::fmod(phi,6.283184); }
    ///Set camera theta angle (in radians)
    void setTheta(double theta) { m_att[2] = ::fmod(theta,6.283184); }

    /// Move camera up/down respecting its current viewpoint and using current scale
    void moveUp(double dist);
    /// Move camera left/right respecting its current viewpoint and using current scale
    void moveLeft(double dist);
    /// Move camera forth/back rescpecting its current viewpoint and using current scale
    void moveForth(double dist);

    /// Turn camera up/down respecting its current viewpoint
    void turnUp(double angle);
    /// Turn camera left/right respecting its current viewpoint
    void turnLeft(double angle);
    /// Roll camera counter-clockwise respecting its current viewpoint
    void roll(double angle);

protected:

    ip::Point3<double> rodrigues() const;

    ip::Point3<double> m_pos; //Position
    ip::Point3<double> m_att; //Angles

    int m_width, m_height;
};

} // namespace msvr

#endif // MSVR_MSRVCAMERA_H
