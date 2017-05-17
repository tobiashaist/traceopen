////////////////////////////////////////////////////////////
/// \file interaction.cc
/// \brief class Interaction
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "interactionray.h"
#include "traceopenerror.h"
#include "ray.h"
#include "logging.h"



//////////////////////////////////////////////////////////////////////
// Denkbar, das die folgende Funktion auch in der Basisklasse Interaction
// sein könnte. Allerdings ist das fraglich. Zunächst straight forward
// (selbst auf di Gefahr einer CodeVerdopplung hin) ist es also
// das schön für jede Lichtklasse extra zu machen.

void InteractionRay::interactElementWithSurfaces(Light* light, ElementWithSurfaces* element)
{
  Ray* li = dynamic_cast<Ray*>(light);
  LOG("InteractionRay::interactElementWithSurfaces");
  
  // TODO Hier kommt nun konkret das Raytracing von Ray durch komplettes element
  // wir machen mal zunächst sequential
  // Dabei ist wesentlich, dass man wirklich erst Schnittpunkt von Ray
  // mit Surface berechnet und dann dort die Interaktionen durchführt.
  // (Bei anderen Elementen muss man natürlich anders vorgehen)
  // (Und bei anderen Lichtarten natürlich auch !)
  
  for(int t=0; t < element->getCntSurfaces(); t++)
    {
      Surface* s = element->getSurface(t);
      // 1. Compute the intersection of Ray with surface
      // (In other cases (elements, lighttypes) this corresponds to propagation
      // For the computation, of course we have to check the different
      // surface types
      
      // 2. Now at this position (light has changed and we have the new
      // position in light stored) we have to take care of all
      // interactions.
#if 0
      if(s->scattering.on() == true)
        if(interactionmodell.mScattering->perform(s->Scattering,
      light) != 0)
            continue;
      PROBLEM 1: Hier bricht sequentiell zusammen.
      PROBLEM 2: Hängt ja von konkreter Surface ab und Schnittpunkt !
	-> erst Schnittpunkt ?!

      if(s->absorption.on() == true)
          if(interactionmodell.mAbsorption->perform(s->Absortion,
      light) != 0)
         -> ray vernichten und return



      // so ... jetzt muss man aber die eigentliche Unterscheidung
      // in SurfaceTypen hinkriegen !!!

      if(s->Type == sphericalSurface)
         interactionmodell.mRefraction(s, light);
      else if(s->Type == grating)
         interactionmodell.mDifraction(s, light);
      ...

#endif







    }
  
}





void InteractionRay::interactParaxialLens(Light* light, ParaxialLens* element)
{
  Ray* li = dynamic_cast<Ray*>(light);
  LOG("InteractionRay::interactParaxialLens");
  
  // TODO Hier kommt nun konkret das Raytracing von Ray durch komplettes element
  // wir machen mal zunächst sequential
  // Dabei ist wesentlich, dass man wirklich erst Schnittpunkt von Ray
  // mit Surface berechnet und dann dort die Interaktionen durchführt.
  // (Bei anderen Elementen muss man natürlich anders vorgehen)
  // (Und bei anderen Lichtarten natürlich auch !)
  
      // 1. Compute the intersection of Ray with surface
      // (In other cases (elements, lighttypes) this corresponds to propagation
      // For the computation, of course we have to check the different
      // surface types
      
      // 2. Now at this position (light has changed and we have the new
      // position in light stored) we have to take care of all

}

