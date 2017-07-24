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
#include "tracing.h"

extern int gInternalSurfaceIndex;  // probably: useless (gInternalElementIndex instead)

// TODO: Oxygen
// TODO: Testcases
// TODO: Const Correctness
//
////////////////////////////////////////////////////////////
/// \param radius radius of curvature
/// \param diameter diameter of surface
/// \param p Position of Scheitel in Space
////////////////////////////////////////////////////////////
SurfaceSpherical::SurfaceSpherical(const real radius, const real diameter,
				   const Point p) : Surface(p, Direction(0,0,0), diameter)
{
  LOG("SurfaceSpherical::CTOR ",  mInternalElementIndex);
  mRadius.set(radius);
}

////////////////////////////////////////////////////////////
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
SurfaceSpherical::SurfaceSpherical(const SurfaceSpherical& surface) :
  Surface(surface), mRadius(surface.mRadius)
{
  mInternalSurfaceIndex = ++gInternalSurfaceIndex;
  LOG("SurfaceSpherical::CTOR copy contrutcor", 
       mInternalElementIndex);
}


//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
/// \return newly created (and copied) Surface
//////////////////////////////////////////////////////////////////////
SurfaceSpherical* SurfaceSpherical::copy(bool deep)
{
  ELOG("SurfaceSpherical::copy", mInternalElementIndex);
  SurfaceSpherical* s = new SurfaceSpherical(*this);
  s->mRadius = mRadius;
  return s;
}

////////////////////////////////////////////////////////////
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
void SurfaceSpherical::swap(SurfaceSpherical& surface) 
{
  ELOG("SurfaceSpherical::swap", mInternalSurfaceIndex);
  Surface::swap(surface);
  std::swap(mRadius, surface.mRadius);
}

////////////////////////////////////////////////////////////
/// Just for debugging
////////////////////////////////////////////////////////////
void SurfaceSpherical::show()
{
  LOG("SurfaceSpherical::show", mInternalElementIndex, mRadius.get());
}

////////////////////////////////////////////////////////////
/// assignment operator
/// \param surface pointer to the surface to be assigned
////////////////////////////////////////////////////////////
SurfaceSpherical& SurfaceSpherical::operator=(SurfaceSpherical& surface) 
{
  ELOG("SurfaceSpherical::operator=", mInternalSurfaceIndex,
       surface.mInternalSurfaceIndex);
  SurfaceSpherical temp(surface);
  swap(surface);
  return* this;
}


//////////////////////////////////////////////////////////////////////
void SurfaceSpherical::callInteraction(Tracing* trace, Light* light)
{
  LOG("SurfaceSpherical::callInteraction ", mInternalElementIndex);
  trace->mInteraction->interactSurfaceSpherical(light, this);
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
