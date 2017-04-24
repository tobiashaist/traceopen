////////////////////////////////////////////////////////////
/// \file point.h
/// \brief include file for class Point
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef POINT_HPP 
#define POINT_HPP

#include "basicdefinitions.h"
#include "parameter.h"

#include <iostream>

////////////////////////////////////////////////////////////
///  \brief Point manages Points/Positions in Space
////////////////////////////////////////////////////////////
///  
///  This is the basic class for representing the position of a point.
///  The point can be given, of course, in different coordinate systems.
///  However, it is stored in "the" one and only global coordinate system.
///  Methods for obtaining the position in other systems are given.
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Point {

public:
  Point(real x=0, real y=0, real z=0);    ///< construction with global coordinates
  
protected:
  Parameter<real> mX;			///< x coordinate in global coordinate system
  Parameter<real> mY;			///< y coordinate in global coordinate system
  Parameter<real> mZ;			///< z coordinate in global coordinate system 
};

#endif
