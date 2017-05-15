////////////////////////////////////////////////////////////
/// \file refraction.h
/// \brief include file for class Interaction
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef REFRACTION_HPP 
#define REFRACTION_HPP


#include "basicdefinitions.h"
#include "light.h"
#include "interaction.h"
#include "element.h"
#include "logging.h"
#include "interaction.h"

#include <iostream>


////////////////////////////////////////////////////////////
///  \brief Most optical components are made out of Surfaces
////////////////////////////////////////////////////////////
///  
///  The abstract base class Refraction is the main class that
///  is responsible for the special interaction refraction
///  Beware: In general, this is done not at a surface but at an element
///
///  \date 15.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

class Refraction : public Interaction 
{
  
public:
  Refraction()
    {
      ELOG("CTOR Refraction");
    }
  virtual ~Refraction();
  // TODO: sollte das nicht protected sein ?!?
  // Generell mal meine alten c++ Sachen durchgehen
  
  virtual void perform(Light* l , Element* e) = 0; /// < perform refraction of light at element
  
protected:
};

#endif
