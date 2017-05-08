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

////////////////////////////////////////////////////////////
/// \param pos Position of Surface in global coordinates
/// \param dir orientation of Surface with respect to global coordinate system
/// \param diameter diameter of surface
////////////////////////////////////////////////////////////
Surface::Surface(const Point pos, const Direction dir, const real diameter) :
  mPosition(pos), mOrientation(dir), mDiameter(diameter)
{
  ELOG("CTOR Surface");
  ELOG("point = ", pos.getZ().get());
}

////////////////////////////////////////////////////////////
/// copy ctor
/// \param surface surface to be used for initialization
////////////////////////////////////////////////////////////
Surface::Surface(const Surface& surface) 
{
  ELOG("COPY CTOR Surface");
  mPosition = surface.mPosition;
  mOrientation = surface.mOrientation;
  mDiameter = surface.mDiameter;
}

////////////////////////////////////////////////////////////
/// just for debugging
////////////////////////////////////////////////////////////
void Surface::show() 
{
  ELOG("SHOW SURFACE");
}

////////////////////////////////////////////////////////////
/// \param surface surface to be swaped with this surface
////////////////////////////////////////////////////////////
void Surface::swap(Surface& surface) 
{
  std::swap(mPosition, surface.mPosition);
  std::swap(mOrientation, surface.mOrientation);
  std::swap(mDiameter, surface.mDiameter);
  std::swap(mSmartPtrSurface, surface.mSmartPtrSurface);  // TODO: to be checked
}

////////////////////////////////////////////////////////////
/// dtor
////////////////////////////////////////////////////////////
Surface::~Surface()
{

}

//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
/// \return raw pointer to the surface that we generated and copied.
//////////////////////////////////////////////////////////////////////
Surface* Surface::copy()
{
  mSmartPtrSurface.reset(new Surface(*this)); // here we generate
  // a new Element and the mSmartPtrSurface gets Ownership for that
    
  return dynamic_cast<Surface*>(mSmartPtrSurface.get());
}

////////////////////////////////////////////////////////////
/// assignment operator
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
Surface& Surface::operator=(Surface& surface) 
{
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
}

////////////////////////////////////////////////////////////
/// \return pointer to Orientation in space
////////////////////////////////////////////////////////////
Parameter<real>* Surface::getDiameter()
{
  return &mDiameter;
}


