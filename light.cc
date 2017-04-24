////////////////////////////////////////////////////////////
/// \file light.cc
/// \brief class Element
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "light.h"


//////////////////////////////////////////////////////////////////////
/// \param t type of light
/// \param lambda wavelength (in m)
/// \param intensity intesity in W/m^2
//////////////////////////////////////////////////////////////////////
Light::Light(const typeLight t, const real lambda, const real intensity ) :
  mLightType(t), mAlive(true)
{
  mLambda.setValue(lambda);
  mIntensity.setValue(intensity);
  mCoherenceLength.setValue(0);
  mOPD.setValue(0);
}

//////////////////////////////////////////////////////////////////////
/// \return true -> ray is alive (not vignetted)
//////////////////////////////////////////////////////////////////////
bool Light::isAlive() const
{
  return mAlive;
}
