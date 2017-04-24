////////////////////////////////////////////////////////////
/// \file ray.h
/// \brief include file for class Ray
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef RAY_HPP 
#define RAY_HPP

#include "basicdefinitions.h"
#include "point.h"
#include "direction.h"
#include "light.h"

#include <iostream>

////////////////////////////////////////////////////////////
///  \brief Ray manages optical (polarized or unpolarized) Rays
////////////////////////////////////////////////////////////
///  
///  This is the basic class for representing light in the geometrical model.
///  The concept of the ray is an idealized one. The ray has zero extension and
///  divergence. Our ray is polarized (Jones Vector) or unpolarized, has one
///  specific wavelength and energy.
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Ray : public Light
{

public:
  Ray(real lambda=500e-9, real intensity=1 ); ///< ctor
  Ray(real lambda, real intensity, Point* const p, Direction* const dir); ///< construction with global coordinates

protected:
  Point mPoint;  		///< start point
  Direction mDirection;         ///< Direction cosines
};

#endif
