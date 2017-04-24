////////////////////////////////////////////////////////////
/// \file refractionwaves.h
/// \brief include file for class RefractionWaves
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef REFRACTIONWAVES_HPP 
#define REFRACTIONWAVES_HPP

#include "basicdefinitions.h"
#include "refraction.h"

#include <iostream>


////////////////////////////////////////////////////////////
///  \brief Refraction of Waves
////////////////////////////////////////////////////////////
///  
///  The abstract base class Refraction is the main class that
///  is responsible for the special interaction refraction
///
///  \date 15.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

class RefractionWaves : public Refraction 
{
public:
  virtual void perform(Light*, Element*  ); ///< trace a wave through element
  
protected:

};

#endif
