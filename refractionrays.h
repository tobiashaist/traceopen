////////////////////////////////////////////////////////////
/// \file refractionrays.h
/// \brief include file for class Interaction
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef REFRACTIONRAYS_HPP 
#define REFRACTIONRAYS_HPP

#include "basicdefinitions.h"
#include "refraction.h"

#include <iostream>


////////////////////////////////////////////////////////////
///  \brief Most optical components are made out of Surfaces
////////////////////////////////////////////////////////////
///  
///  The abstract base class Refraction is the main class that
///  is responsible for the special interaction refraction
///
///  \date 15.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

class RefractionRays : public Refraction 
{
  
public:
  virtual void perform(Light* light , Element* element); ///< perform refraction of rays through element
  
protected:

};

#endif
