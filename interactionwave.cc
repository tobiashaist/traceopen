////////////////////////////////////////////////////////////
/// \file interactionwave.cc
/// \brief class Interaction
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "wave.h"
#include "interactionwave.h"
#include "traceopenerror.h"
#include "logging.h"


// TODO: Up till now just copied (old) things out of InteractionRay
// and changed the names ... does not make any sense and just shows
// that it compiles and the correct functions are called.
// So: clear the unnecessary things out (it will only bemuse the reader)
//

void InteractionWave::interactElement(Light* light, Element* element)
{
  Wave* li = dynamic_cast<Wave*>(light);
  LOG("InteractionWave::interactElement");
  
  // TODO Hier kommt nun konkret das Raytracing von Ray durch komplettes element
  // wir machen mal zunächst sequential
  // Dabei ist wesentlich, dass man wirklich erst Schnittpunkt von Ray
  // mit Surface berechnet und dann dort die Interaktionen durchführt.
  // (Bei anderen Elementen muss man natürlich anders vorgehen)
  // (Und bei anderen Lichtarten natürlich auch !)
  
  for(int t=0; t < element->getCntSubElements(); t++)
    {
      Element* s = element->getElement(t);
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



////////////////////////////////////////////////////////////
void InteractionWave::interactParaxialLens(Light* light, ParaxialLens* plens)
{
  LOG("InteractionWave::interactParaxialLens");
  Wave* wave = dynamic_cast<Wave*>(light);

  // 1. Intersection
  //  computeIntersectionWithParaxialLens(wave, plens);

  // 2. Interaction
  // In general we need the local surface normal and of course the ray direction
  // to be able to compute the interaction
  // we compute this at the position of the Ray

  //  Direction normal = plens->computeSurfaceNormal(wave->getPoint());

  // Beware: Only For Ray Bundles we will generate more Rays in than out
  // Here (in the interactionRay class) one ray stays one ray.
  // and there is one "LeadingInteraction" (e.g. diffraction for a grating)
  // which will be used during interaction.
  // This leading interaction can be set by the user (e.g. for ghost analysis by hand)

  //  doLocalInteraction(wave, normal);
		     
}


////////////////////////////////////////////////////////////
void InteractionWave::interactSurfaceSpherical(Light* light, SurfaceSpherical* surface)
{
  LOG("InteractionWave::interactSurfaceSpherical");
  Wave* wave = dynamic_cast<Wave*>(light);

  //  doLocalInteraction(ray, normal);
		     
}

