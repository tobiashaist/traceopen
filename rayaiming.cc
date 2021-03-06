////////////////////////////////////////////////////////////
/// \file rayaiming.cc
/// \brief class Ray Aiming
///  \date 22.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "rayaiming.h"


//////////////////////////////////////////////////////////////////////
/// \param light light to be aimed (Input and Output !)
/// \param system optical system where we aim
/// \param p Point that we aim to (e.g. a position in the stop plane)
//////////////////////////////////////////////////////////////////////
void RayAiming::aim(Light* light, OpticalSystem* system, Point* p)
{
  ;
}

//////////////////////////////////////////////////////////////////////
/// \return true -> ray is alive (not vignetted)
//////////////////////////////////////////////////////////////////////
typeRayAiming RayAiming::getType()
{
  return mType;
}


//////////////////////////////////////////////////////////////////////
/// \return true -> ray is alive (not vignetted)
//////////////////////////////////////////////////////////////////////
void RayAiming::setType(typeRayAiming type)
{
  mType = type;
}


