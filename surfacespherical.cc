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

////////////////////////////////////////////////////////////
/// \param radius radius of curvature
/// \param diameter diameter of surface
/// \param p Position of Scheitel in Space
////////////////////////////////////////////////////////////
SurfaceSpherical::SurfaceSpherical(const real radius, const real diameter,
				   const Point p) : Surface(p, Direction(0,0,0), diameter)
{
  mRadius.set(radius);
}

////////////////////////////////////////////////////////////
/// \return pointer to the Parameter for radius
////////////////////////////////////////////////////////////
Parameter<real>* SurfaceSpherical::getRadiusPointer()
{
  return &mRadius;
}
