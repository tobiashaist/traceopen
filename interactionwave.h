////////////////////////////////////////////////////////////
/// \file interactionwave.h
/// \brief include file for class InteractionRay
///  \date 22.07.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 


#ifndef INTERACTIONWAVE_HPP 

#define INTERACTIONWAVE_HPP

#include "basicdefinitions.h"
#include "light.h"
#include "element.h"
#include "paraxiallens.h"
#include "interaction.h"
#include <iostream>


////////////////////////////////////////////////////////////
///  \brief  InteractionWave is responsible for the interactions for Waves.
////////////////////////////////////////////////////////////
/// 
///  Up till now this class is not used at all, apart from showing that
///  that it will work that way
///  It is not planned to put any effort at the moment into the implementation.
///  So just put in empty methods if necessary.
///
///  \date 22.7.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class SphericalSurface;

class InteractionWave : public Interaction
{
  
public:
  virtual void interactElement(Light* light, Element* element);
  virtual void interactParaxialLens(Light* light, ParaxialLens* element);
  virtual void interactSurfaceSpherical(Light* light, SurfaceSpherical* element);

};

#endif
