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
/// Important: For some elements (most important: ElementWithSurfaces and Paraxial)
/// we mix propagation and interaction. Interaction then means that rays
/// will first travels until the intersection and we decide about the
/// concrete interactions. Actually, since this is the most often used case,
/// it is something like a standard case.... on the other hand, it is
/// not ! Reason for doing this: Speed.
///
/// Beware: In contrast to Zemax an Paraxial lens or a spherical surface is not given by
/// lens AND THEN DISTANCE TO THE NEXT ELEMENT
/// But by the position of the lens.
/// For the raytracing this means that we FIRST propagate and then have the interaction
///
/// 
/// What interactions do we have to take care of ?
/// - Refraction
/// - Paraxial Refraction
/// - Scattering
/// - Absorption
/// - Reflection
/// - Diffraction
///
/// (All these things are different with polarization turned on.)
///
/// Now ... of course some elements have multiple interfaces or volumes and
/// and therefore we can have multiple interactions going on ....
/// So: For such elements (especially conventional lenses) we have to do
/// the interactions on a surface by surface basis
/// Anyway, most elements (even GRIN lenses) have a least a start and
/// an end surface ....
/// and at these surfaces we have refraction, scattering etc ....

#include "ray.h"
#include "interactionray.h"
#include "traceopenerror.h"
#include "logging.h"

// TODO: Doxygen
// TODO: Testcases
// TODO: Rethink what should go in the base class Interaction and
// what we want to have only for rays
//////////////////////////////////////////////////////////////////////
// Denkbar, das die folgende Funktion auch in der Basisklasse Interaction
// sein könnte. Allerdings ist das fraglich. Zunächst straight forward
// (selbst auf die Gefahr einer CodeVerdopplung hin) ist es also
// das schön für jede Lichtklasse extra zu machen.

// TODO: Very unsure if we still need the following
// Anyway: Some basic thoughts might be useful.
// In the current stage more or less nothing is done and only
// the structure shows that it is possible to do it that way.
void InteractionRay::interactElement(Light* light, Element* element)
{
  Ray* li = dynamic_cast<Ray*>(light);
  LOG("InteractionRay::interactElement");
  
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


	      
      //  In the past we thought that we have to do something like this here ...
      //  Now, we would rather replace with the individual functions 	      
      if(s->Type == sphericalSurface)
         interactionmodell.mRefraction(s, light);
      else if(s->Type == grating)
         interactionmodell.mDifraction(s, light);
      ...

#endif

   }
  
}


////////////////////////////////////////////////////////////
// TODO: Please recheck. I have major doubts if it is correct
void InteractionRay::computeIntersectionWithParaxialLens(Ray* ray, ParaxialLens* lens)
{
  LOG("InteractionRay::computeIntersectionWithParaxialLens");
  // TODO: Up till now, no shifts, tilts, ...
  //    only axial (z) position .... not quite general :)
  
  // 1. Compute the intersection of Ray with surface
  // (In other cases (elements, lighttypes) this corresponds to propagation
  // For the computation, of course we have to check the different
   // surface types

  real zlens = lens->getPosition()->zValue();
  real xangle = ray->getDirCosX();
  real yangle = ray->getDirCosY();
  real zangle = ray->getDirCosZ();
  real x0 = ray->getX();
  real z0 = ray->getZ();
  real y0 = ray->getY();

  // Now, we have to find the length of the ray between
  // current start position and the plane of the paraxial lens.
  real thickness = (zlens-z0)/zangle;

  // Now we compute (vectorial): r' = r + distance * vec(k)
  real y = y0 + thickness * yangle;
  real x = x0 + thickness * xangle;
  real z = z0 + thickness * zangle;
  ray->setY(y);
  ray->setX(x);
  ray->setZ(z);
}

// TODO: Please recheck. I have major doubts if it is correct
////////////////////////////////////////////////////////////
void InteractionRay::interactParaxialLens(Light* light, ParaxialLens* plens)
{
  LOG("InteractionRay::interactParaxialLens");
  Ray* ray = dynamic_cast<Ray*>(light);

  // 1. Intersection
  computeIntersectionWithParaxialLens(ray, plens);

  // 2. Interaction
  // In general we need the local surface normal and of course the ray direction
  // to be able to compute the interaction
  // we compute this at the position of the Ray

  Direction normal = plens->computeSurfaceNormal(ray->getPoint());

  // Beware: Only For Ray Bundles we will generate more Rays in than out
  // Here (in the interactionRay class) one ray stays one ray.
  // and there is one "LeadingInteraction" (e.g. diffraction for a grating)
  // which will be used during interaction.
  // This leading interaction can be set by the user (e.g. for ghost analysis by hand)

  doLocalInteraction(ray, normal);
		     
}

// TODO: to be filled
////////////////////////////////////////////////////////////
void InteractionRay::interactSurfaceSpherical(Light* light, SurfaceSpherical* surface)
{
  LOG("InteractionRay::interactSurfaceSpherical");
  Ray* ray = dynamic_cast<Ray*>(light);

  //  doLocalInteraction(ray, normal);
		     
}

// TODO: to be filled
////////////////////////////////////////////////////////////
void InteractionRay::doLocalInteraction(Ray* ray, Direction normal)
{


}
