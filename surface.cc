////////////////////////////////////////////////////////////
/// \file surface.cc
/// \brief class Surface
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "surface.h"
#include "logging.h"

// TODO: Check for alle Ctors and copies if the base class is/should
// be also copied.
// TODO: Testcases to be written

int gInternalSurfaceIndex=0;  // TODO mal noch sinnvoller machen (static)

////////////////////////////////////////////////////////////
/// \param pos Position of Surface in global coordinates
/// \param dir orientation of Surface with respect to global coordinate system
/// \param diameter diameter of surface
////////////////////////////////////////////////////////////
Surface::Surface(const Point pos, const Direction dir, const real diameter) :
mDiameter(diameter)
{
  mInternalSurfaceIndex = ++gInternalSurfaceIndex;
  ELOG("Surface::ctor", pos.z_const().get());
  mPosition = pos;
  mOrientation = dir;
}

////////////////////////////////////////////////////////////
/// copy ctor
/// \param surface surface to be used for initialization
////////////////////////////////////////////////////////////
Surface::Surface(const Surface& surface) 
{
  // TODO: not enough
  mInternalSurfaceIndex = ++gInternalSurfaceIndex;
  ELOG("Surface::copy ctor Surface");
  mPosition = surface.mPosition;
  mOrientation = surface.mOrientation;
  mDiameter = surface.mDiameter;
}

////////////////////////////////////////////////////////////
/// just for debugging
////////////////////////////////////////////////////////////
void Surface::show() 
{
  LOG("Surface::show Element Index", mInternalElementIndex);
}

////////////////////////////////////////////////////////////
/// \param surface surface to be swaped with this surface
////////////////////////////////////////////////////////////
void Surface::swap(Surface& surface) 
{
  // TODO: Not enough
  std::swap(mPosition, surface.mPosition);
  std::swap(mOrientation, surface.mOrientation);
  std::swap(mDiameter, surface.mDiameter);
}

////////////////////////////////////////////////////////////
/// dtor
////////////////////////////////////////////////////////////
Surface::~Surface()
{
  ELOG("Surface::dtor");
}

//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
/// \return raw pointer to the surface that we generated and copied.
//////////////////////////////////////////////////////////////////////
Surface* Surface::copy(bool deep)
{
  ELOG("Surface::copy");
  Surface* s = new Surface(*this);
  // TODO: Copying ! Deep !
  return s;
}

//////////////////////////////////////////////////////////////////////
void Surface::callInteraction(Tracing* trace, Light* light)
{
  LOG("Surface::callInteraction", mInternalElementIndex);
  // TODO: Do we really need this function ? Can we use this ?
  // As a general thing ?
}


////////////////////////////////////////////////////////////
/// assignment operator
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
Surface& Surface::operator=(Surface& surface) 
{
  // TOOD: Check if correct
  LOG("Surface::operator=");
  Surface temp(surface);
  swap(surface);
  return* this;
}

////////////////////////////////////////////////////////////
/// \return pointer to Position in space
////////////////////////////////////////////////////////////
Point* Surface::getPosition()
{
  return &mPosition;
}


////////////////////////////////////////////////////////////
/// \return pointer to Position in space
////////////////////////////////////////////////////////////
Direction* Surface::getOrientation()
{
  return &mOrientation;
  // TODO: In general how do we generall do access to Directions, Positions
  // and Parameters
}

////////////////////////////////////////////////////////////
/// \return pointer to Orientation in space
////////////////////////////////////////////////////////////
Parameter<real>* Surface::getDiameter()
{
  return &mDiameter;
}


