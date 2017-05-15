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
  mLightType(t), mAlive(true), mUsesPolarization(false)
{
  mLambda.set(lambda);
  mIntensity.set(intensity);
  mCoherenceLength.set(0);
  mOPD.set(0);
}

//////////////////////////////////////////////////////////////////////
Light::~Light()
{

}

//////////////////////////////////////////////////////////////////////
/// \return true -> ray is alive (not vignetted)
//////////////////////////////////////////////////////////////////////
bool Light::isAlive() const
{
  return mAlive;
}

//////////////////////////////////////////////////////////////////////
/// \return true -> polarization should be used
//////////////////////////////////////////////////////////////////////
bool Light::isUsingPolarization() const
{
  return mUsesPolarization;
}

//////////////////////////////////////////////////////////////////////
/// \return true -> polarization should be used
//////////////////////////////////////////////////////////////////////
void Light::setUsingPolarization(bool useit) 
{
  mUsesPolarization = useit;
}
