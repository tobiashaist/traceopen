////////////////////////////////////////////////////////////
/// \file direction.h
/// \brief include file for class Direction
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef DIRECTION_HPP 
#define DIRECTION_HPP

#include "basicdefinitions.h"
#include "parameter.h"

#include <iostream>


////////////////////////////////////////////////////////////
///  \brief Direction manages Directions/Orientations in Space
////////////////////////////////////////////////////////////
///  
///  This is the basic class for representing the direction (e.g. of a ray).
///  The direction can be given, of course, in different coordinate systems and
///  with different representations which have different advantages.
///  However, it is internally stored in "the" one and only global coordinate system.
///  in the direction cosine way. 
///  Methods for obtaining the direction in other systems and other
///  representation are given.
///  Angles are given in radians.
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Direction {

public:
  /// ! also Copy Ctor and assignment operation work correctly (see test_003)
  
  explicit Direction(real alpha=0, real beta=0, real gamma=0);  ///< construction with global coordinates

  Parameter<real>& dirCosX(void) {return mDirCosX;}  ///< get reference onto point x global coordinate
  Parameter<real>& dirCosY(void) {return mDirCosY;}  ///< get reference onto point y global coordinate
  Parameter<real>& dirCosZ(void) {return mDirCosZ;}  ///< get reference onto point z global coordinate

  const Parameter<real>& dirCosX_const(void) const {return mDirCosX;} ///< get reference onto point x global coordinate
  const Parameter<real>& dirCosY_const(void) const {return mDirCosY;} ///< get reference onto point x global coordinate
  const Parameter<real>& dirCosZ_const(void) const {return mDirCosZ;} ///< get reference onto point x global coordinate

  real dirCosXValue(void) {return mDirCosX.get();}  ///< get value of direction cosine x
  real dirCosYValue(void) {return mDirCosY.get();}  ///< get value of direction cosine y
  real dirCosZValue(void) {return mDirCosZ.get();}  ///< get value of direction cosine z
  
protected:
  Parameter<real> mDirCosX;    ///< direction cosine x-axis in global coordinate system
  Parameter<real> mDirCosY;    ///< direction cosine y-axis in global coordinate system
  Parameter<real> mDirCosZ;    ///< direction cosine z-axis in global coordinate system 
};

#endif
