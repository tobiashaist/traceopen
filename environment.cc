////////////////////////////////////////////////////////////
/// \file environment.cc
/// \brief class Environment
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "material.h"



////////////////////////////////////////////////////////////
/// \param n refractive index
////////////////////////////////////////////////////////////
Environment::Environment(const real temperature, const real pressure) :
  mTemperature(temperature), mPressure(pressure)
{
  
}

////////////////////////////////////////////////////////////
/// \param n refractive index
////////////////////////////////////////////////////////////
real Environment::getTemperature() const 
{
  return mTemperature.get();
}

					       

