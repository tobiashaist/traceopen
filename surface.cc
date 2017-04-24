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

////////////////////////////////////////////////////////////
/// \param pos Position of Surface in global coordinates
/// \param dir orientation of Surface with respect to global coordinate system
/// \param diameter diameter of surface
////////////////////////////////////////////////////////////
Surface::Surface(const Point pos, const Direction dir, const real diameter) :
  mPosition(pos), mOrientation(dir), mDiameter(diameter)
{

}

////////////////////////////////////////////////////////////
Surface::~Surface()
{

}
