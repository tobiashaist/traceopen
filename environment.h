////////////////////////////////////////////////////////////
/// \file enviroment.h
/// \brief include file for class Enviroment
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef ENVIROMENT_HPP 
#define ENVIROMENT_HPP

#include <complex>
#include <string>
#include "basicdefinitions.h"
#include "parameter.h"




////////////////////////////////////////////////////////////
///  \brief Enviroment is responsible for storing/computing enviromental parameters  
////////////////////////////////////////////////////////////
///  
///
////////////////////////////////////////////////////////////
class Environment
{
  
public:

  Environment(real temperature, real pressure);  ///< ctor
  real getTemperature() const;                  ///< get function
  void setTemperature(real temperature);  ///< set function

 protected:
  Parameter<real> mTemperature;	        ///< Temperature in K
  Parameter<real> mPressure;	        ///< Pressure in bar
};

#endif
