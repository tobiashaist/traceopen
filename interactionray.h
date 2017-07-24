////////////////////////////////////////////////////////////
/// \file interactionray.h
/// \brief include file for class InteractionRay
///  \date 15.05.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 



#ifndef INTERACTIONRAY_HPP 

#define INTERACTIONRAY_HPP

#include "basicdefinitions.h"
#include "light.h"
#include "element.h"
#include "paraxiallens.h"
#include "interaction.h"
#include <iostream>

// TODO: Extension for a lot useful things
// TODO: global functions for coordinate transform (or put it into Point or Direction)

////////////////////////////////////////////////////////////
///  \brief InteractionRay is responsible for the interactions for rays.
///  
/// 
///  \date 15.5.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class SphericalSurface;

class InteractionRay : public Interaction
{
public:
  virtual void interactElement(Light* light, Element* element);
  virtual void interactParaxialLens(Light* light, ParaxialLens* element);
  virtual void interactSurfaceSpherical(Light* light, SurfaceSpherical* element);
  
  void computeIntersectionWithParaxialLens(Ray* ray, ParaxialLens* lens);
  void doLocalInteraction(Ray* ray, Direction normal);
};

#endif
