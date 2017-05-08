////////////////////////////////////////////////////////////
/// \file surface.cc
/// \brief class Element
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

////////////////////////////////////////////////////////////
Surface::Surface(const Surface& surf) 
{
  ELOG("COPY CTOR Surface");
  mPosition = surf.mPosition;
  mOrientation = surf.mOrientation;
  mDiameter = surf.mDiameter;
}



////////////////////////////////////////////////////////////
void Surface::show() 
{
  ELOG("SHOW SURFACE");
}

////////////////////////////////////////////////////////////
void Surface::swap(Surface& surf) 
{
  std::swap(mPosition, surf.mPosition);
  std::swap(mOrientation, surf.mOrientation);
  std::swap(mDiameter, surf.mDiameter);
  std::swap(mSmartPtrSurface, surf.mSmartPtrSurface);  // TODO: to be checked
}

////////////////////////////////////////////////////////////
Surface::~Surface()
{

}

//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
//////////////////////////////////////////////////////////////////////
Surface* Surface::copy()
{
  mSmartPtrSurface.reset(new Surface(*this)); // here we generate
  // a new Element and the mSmartPtrSurface gets Ownership for that
    
  return dynamic_cast<Surface*>(mSmartPtrSurface.get());
}

////////////////////////////////////////////////////////////
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
/// \return pointer to Position in space
////////////////////////////////////////////////////////////
Parameter<real>* Surface::getDiameter()
{
  return &mDiameter;
}


