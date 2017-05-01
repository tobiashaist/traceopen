////////////////////////////////////////////////////////////
/// \file raybundle.cc
/// \brief class RayBundle
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "raybundle.h"
#include "logging.h"

//////////////////////////////////////////////////////////////////////
/// \param lambda wavelength (in m)
/// \param intensity intesity in W/m^2
//////////////////////////////////////////////////////////////////////
RayBundle::RayBundle() 
{
  LOG("RayBundle ctor A");
}

//////////////////////////////////////////////////////////////////////
/// \param dir start direction of the ray (pointer due to efficiency)
//////////////////////////////////////////////////////////////////////
void RayBundle::generateCone(int numberOfRays,  real wavelength, real intensity,
			     typeRayBundlePattern pattern, Point* const p,
			     Direction* const dir, real angle) 
{
  LOG("RayBundle.generateCone");
  // ---------------- TODO !

}

