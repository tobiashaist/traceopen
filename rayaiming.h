////////////////////////////////////////////////////////////
/// \file rayaiming.h
/// \brief include file for class RayAiming
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 1999
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef RAYAIMING_HPP 
#define RAYAIMING_HPP

#include "basicdefinitions.h"
#include "light.h"
#include "opticalsystem.h"

#include <iostream>

enum typeRayAiming {typeRayAimingNone, typeRayAimingParaxial, typeRayAimingExact};

////////////////////////////////////////////////////////////
///  \brief RayAiming implements rayaiming :)  
////////////////////////////////////////////////////////////
///  
/// RayAiming is the process to find (for a given start position of a ray)
/// the right direction to later pass through another point (typically given
/// in the plane of the (aperture) stop).
/// More or less intelligent algorithms for that are possible, also user
/// assistance is possible.
/// And since rayaiming is necessary typically for every pass during optimization
/// it is also beneficial to do this quite fast...
/// Lots of possibilities for the future. Also for subclasses.
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class RayAiming
{

public:
  
  void aim(Light* light, OpticalSystem* system, Point* p); ///< aim for the point p
  void setType(typeRayAiming);				   ///< set the RayAiming Type
  typeRayAiming getType(void);				   ///< get the RayAiming Type

protected:
  typeRayAiming mType;    ///< Type of RayAiming
};

#endif
