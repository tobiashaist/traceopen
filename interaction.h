////////////////////////////////////////////////////////////
/// \file interaction.h
/// \brief include file for class Interaction
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 



#ifndef INTERACTION_HPP 
#define INTERACTION_HPP

#include "basicdefinitions.h"
#include "light.h"
#include "element.h"
#include <iostream>




////////////////////////////////////////////////////////////
///  \brief Most optical components are made out of Surfaces
////////////////////////////////////////////////////////////
///  
///  The abstract base class Interaction is the main class that
///  is responsible for interactions like refraction, refraction etc.
///  I thinks it is and will still be just an interface.
/// 
///  \date 15.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

class Interaction 
{
  
public:
  Interaction();			    ///< dtor
  virtual ~Interaction();		    ///< dtor

  virtual void perform(Light*, Element* e) = 0;
};

#endif
