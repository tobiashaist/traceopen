////////////////////////////////////////////////////////////
/// \file point.cc
/// \brief class Point
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "point.h"

//////////////////////////////////////////////////////////////////////
/// \param x global x coordinate of point
/// \param y global y coordinate of point
/// \param z global z coordinate of point
//////////////////////////////////////////////////////////////////////
Point::Point(const real x, const real y, const real z) : mX(x), mY(y), mZ(z)
{
  ;
}


//////////////////////////////////////////////////////////////////////
void Point::swap(Point& point1)
{
  std::swap(mX, point1.mX);
  std::swap(mY, point1.mY);
  std::swap(mZ, point1.mZ);
}

