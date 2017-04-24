////////////////////////////////////////////////////////////
/// \file ray.cc
/// \brief class Ray
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "ray.h"
#include "logging.h"

//////////////////////////////////////////////////////////////////////
/// \param lambda wavelength (in m)
/// \param intensity intesity in W/m^2
//////////////////////////////////////////////////////////////////////
Ray::Ray(const real lambda, const real intensity) :
  Light(typeLightRay, lambda, intensity)
{
  LOG("Ray ctor A");
}

//////////////////////////////////////////////////////////////////////
/// \param lambda wavelength (in m)
/// \param intensity intesity in W/m^2
/// \param p start point of the ray (pointer due to efficiency)
/// \param dir start direction of the ray (pointer due to efficiency)
//////////////////////////////////////////////////////////////////////
Ray::Ray(const real lambda, const real intensity, Point* const p, Direction* const dir) :
  Light(typeLightRay, lambda, intensity), mPoint(*p), mDirection(*dir)
{
  LOG("Ray ctor B");

}
