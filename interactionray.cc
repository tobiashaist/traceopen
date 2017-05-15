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
  
  for(int t=0; t < element->getCntSurfaces(); t++)
    {
      Surface* s = element->getSurface(t);
#if 0
      if(s->scattering.on() == true)
        if(interactionmodell.mScattering->perform(s->Scattering,
      light) != 0)
            continue;  PROBLEM: Hier bricht sequentiell zusammen.
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

