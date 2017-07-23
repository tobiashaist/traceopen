////////////////////////////////////////////////////////////
/// \file tracing.cc
/// \brief class Tracing
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "ray.h"
#include "wave.h"
#include "tracing.h"
#include "interactionray.h"
#include "interactionwave.h"
#include "logging.h"

//////////////////////////////////////////////////////////////////////
Tracing::Tracing() : mRayAiming(NULL)
{

}

//////////////////////////////////////////////////////////////////////
Tracing::~Tracing()
{
  if(mRayAiming != NULL)
    delete mRayAiming;
}

//////////////////////////////////////////////////////////////////////
/// \param l light to be traced
/// \param s optical system through which we want to trace
//////////////////////////////////////////////////////////////////////
void Tracing::trace() 
{
  // This is the main entry point for tracing light trough a complete
  // optical system. It has to work with rays, raybundles, waves etc.
  // and of course the optical system can contain whatever elements.
  //
  // We also have to take care of non-sequential issues !
  //
  // for the Moment: we just do sequential

  ELOG("Tracing::trace");

  // Dependend on the defined interaction per Surface we have to
  // call the correct interaction function.
  //
  // But: One Element might have different interactions (e.g. one side
  // a DOE the other refraction)
  // But we can also not set this interaction to the surface because
  // some elements might not have surfaces but would be more volumes.
  // So, the only solution is that the element has the power to decide
  // which interactions to use locally.
  // But this means that tracing should give its interaction model
  // (which more or less stores e.g. what KIND OF REFRACTION really would
  // be used (more or less: ray based or wave based))
  // to the element ?
  // No. That would put all kind of code concerning optical simulation
  // (waves, rays, etc ....) into the Element class. That would make
  // this class too complicated.
  // We need something better here !!!!

  for(int t=0; t < mSystem->getCntElements(); t++)
    {
      Element* e = mSystem->getElement(t);
      LOG("in for loop bevor show and now tracing Element", mLight->getType());
      //      e->show();
      e->callInteraction(this, mLight);
    }
}


//////////////////////////////////////////////////////////////////////
/// \param l light to be traced
/// \param s optical system through which we want to trace
//////////////////////////////////////////////////////////////////////
void Tracing::computeElementDiameters(Ray* light, OpticalSystem* osystem) 
{
  // Here, we will have to use RayAiming and the aperture things
  // of the optical system to first find the marginal Ray and
  // then we have that ray intersections to define the diameters (or more complex:
  // the aperture shapes

  // TODO: How do we handle more complex shapes of the Elements (e.g.
  // rectangular ones ?
  // For simple x,y we could use marginal rays in meridoneal and sagital plane
  // but an rectangular element might be even rotated ! or it might be hexagonal etc.
  // The point is: For such Cases things get arbitrary complex.
  // A quite general approach would be to trace lots (10.000) random Rays (which
  // are "OK" according to our (whatever !) definition of "Aperture") through
  // the system and check at the elements with the complicated apertures how we
  // have to set the parameters (e.g. of the octaeder) so that it works
  // This is of course a) time consuming and b) not easy to implement because
  // it should work with all kinds of Aperture shapes.
  // Therefore it will be best to a) start with circular
  // apertures (computeElementDiameters), then got to simple x/y rectangles
  // and then think of more complicated things.
  
}


//////////////////////////////////////////////////////////////////////
/// \param l light based on which all interactions are to be set
//////////////////////////////////////////////////////////////////////
void Tracing::init(Light* light, LowLevelSystem* system) 
{
  ELOG("Done setGlobalInteractions");

  if(light->getType() == typeLightRay)
    mInteraction = new InteractionRay;
  else
    mInteraction = new InteractionWave;
  
  mLight = light;
  mSystem = system;

  // The following will crash because mInteraction is not set suitable
#if 0
  switch(light->getType())
    {
    case typeLightRay:
      mRayAiming = new RayAiming;   // standard Ray-based RayAiming
    }
  #endif
}


