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
  explicit Ray(real lambda=500e-9, real intensity=1 ); ///< ctor
  Ray(real lambda, real intensity, Point* const p, Direction* const dir); ///< construction with global coordinates
  Point& getPoint();	               ///< Access to current origin point of ray, arbitrary coordinate
  void setPoint(Point point);    ///< set the current origin point of ray, arbitrary coordinates


  virtual void show();
  
  real getX() const;           ///< get the x coordinate of the point of the ray, global coordinates
  real getY() const;           ///< get the y coordinate of the point of the ray, global coordinates
  real getZ() const;           ///< get the z coordinate of the point of the ray, global coordinates
  void setX(real x );           ///< set the x coordinate of the point of the ray, global coordinates
  void setY(real y );           ///< set the y coordinate of the point of the ray, global coordinates
  void setZ(real z );           ///< set the z coordinate of the point of the ray, global coordinates
  void setXYZ(real x, real y, real z );           ///< set the coordinates of the point of the ray, global coordinates

  real getDirCosX() const; ///< get the direction cosine to the x-axis, global coordinates
  real getDirCosY() const; ///< get the direction cosine to the y-axis, global coordinates
  real getDirCosZ() const; ///< get the direction cosine to the z-axis, global coordinates
  void setDirCosX(real x); ///< set the direction cosine to the x-axis, global coordinates
  void setDirCosY(real y); ///< set the direction cosine to the y-axis, global coordinates
  void setDirCosZ(real z); ///< set the direction cosine to the z-axis, global coordinates
  void setDirCosXYZ(real x, real y, real z );        ///< set the coordinates of the directionCosines

  
protected:
  Point mPoint;  		    ///< current origin point of ray
  Direction mDirection;         ///< Direction cosines
};

#endif
