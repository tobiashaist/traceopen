////////////////////////////////////////////////////////////
/// \file surfacespherical.cc
/// \brief class Element
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "surfacespherical.h"
#include "logging.h"

int gInternalSurfaceIndex=0;  // TODO mal noch sinnvoller machen (static)
////////////////////////////////////////////////////////////
/// \param radius radius of curvature
/// \param diameter diameter of surface
/// \param p Position of Scheitel in Space
////////////////////////////////////////////////////////////
SurfaceSpherical::SurfaceSpherical(const real radius, const real diameter,
				   const Point p) : Surface(p, Direction(0,0,0), diameter)
{
  mInternalSurfaceIndex = ++gInternalSurfaceIndex;
  LOG("SurfaceSpherical::CTOR ", mInternalSurfaceIndex);
  mRadius.set(radius);
}


//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
/// \return newly created (and copied) Surface
//////////////////////////////////////////////////////////////////////
SurfaceSpherical* SurfaceSpherical::copy()
{
  LOG("SurfaceSpherical::copy", mInternalSurfaceIndex);
  mSmartPtrSurface.reset(new SurfaceSpherical(*this)); // here we generate
  // a new Element and the mSmartPtrSurface gets Ownership for that
    
  return dynamic_cast<SurfaceSpherical*>(mSmartPtrSurface.get());
}

////////////////////////////////////////////////////////////
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
void SurfaceSpherical::swap(SurfaceSpherical& surface) 
{
  LOG("SurfaceSpherical::swap", mInternalSurfaceIndex);
  Surface::swap(surface);
  std::swap(mRadius, surface.mRadius);
}

////////////////////////////////////////////////////////////
/// Just for debugging
////////////////////////////////////////////////////////////
void SurfaceSpherical::show()
{
  LOG("SurfaceSpherical::show", mInternalSurfaceIndex);
}

////////////////////////////////////////////////////////////
/// assignment operator
/// \param surface pointer to the surface to be assigned
////////////////////////////////////////////////////////////
SurfaceSpherical& SurfaceSpherical::operator=(SurfaceSpherical& surface) 
{
  SurfaceSpherical temp(surface);
  swap(surface);
  return* this;
}

////////////////////////////////////////////////////////////
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
SurfaceSpherical::SurfaceSpherical(const SurfaceSpherical& surface) :
  Surface(surface), mRadius(surface.mRadius)
{
  mInternalSurfaceIndex = ++gInternalSurfaceIndex;
  LOG("SurfaceSpherical::CTOR copy contrutcor", mInternalSurfaceIndex);
}



////////////////////////////////////////////////////////////
/// \return pointer to the Parameter for radius of curvature
////////////////////////////////////////////////////////////
Parameter<real>* SurfaceSpherical::getRadiusPointer()
{
  return &mRadius;
}

////////////////////////////////////////////////////////////
/// \return directly get the radius of curvature
////////////////////////////////////////////////////////////
real SurfaceSpherical::getRadius()
{
  return mRadius.get();
}
