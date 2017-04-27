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
#include "tracing.h"
#include "refraction.h"
#include "logging.h"



//////////////////////////////////////////////////////////////////////
Tracing::Tracing() : mInteraction(NULL), mRayAiming(NULL)
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
void Tracing::trace() const
{
  LOG("Tracing starts");
  mInteraction->mRefraction->perform(mLight, mSystem->getElement(0));
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
void Tracing::init(Light* light, OpticalSystem* osystem) 
{
  mLight = light;
  mSystem = osystem;
  
  mInteraction->setGlobalInteractions(light);
  switch(light->getType())
    {
    case typeLightRay:
      mRayAiming = new RayAiming;   // standard Ray-based RayAiming
    }
}

//////////////////////////////////////////////////////////////////////
/// \param i interaction that will be used for tracing through
//////////////////////////////////////////////////////////////////////
void Tracing::setInteraction(Interaction* const i)
{
  mInteraction = i;
};
