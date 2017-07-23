////////////////////////////////////////////////////////////
/// \file tracing.h
/// \brief include file for class Tracing
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef TRACING_HPP 
#define TRACING_HPP

#include "basicdefinitions.h"
#include "light.h"
#include "ray.h"
#include "lowlevelsystem.h"
#include "rayaiming.h"
#include "interaction.h"
#include <iostream>

////////////////////////////////////////////////////////////
///  \brief 
///  The abstract base class Tracing is the main container for 
///  propagation and interaction.
///
/// Unclear Design decision: RayAiming. In principle one would first think that
/// this is only necessary for Rays and RayBundles but that
/// is (I think) wrong. Also for tracing e.g. waves some concept is
/// necessary to "aim".
/// Therefore we include it here.
/// However, we implement it as a pointer because it might be
/// useful to later make subclasses of RayAiming (for waves)
///
/// computeElementDiameters: Here for Rays everything would be "easy"
/// But what would happen for a wave ?
/// Typically, we would not call that function because tradionally we could
/// set the diameters as fixed or we would still use Rays to decide about
/// the diameters. Of course it would be possible to extend that concept
/// for more complicated things ... e.g. a CGH is included and again the
/// method computeElementDiameters should be able to compute the correct
/// diameters.
/// This is not an easy task because that would strongly depend on the
/// application. We therefore conclude that the user (of the class library)
/// is reponsible in such cases to write his own function which is able
/// to compute Diameters. Just by Hand and without touching our classes.
/// 
///  \date 15.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Tracing 
{
  
public:
  Tracing();			///< ctor
  ~Tracing();			///< dtor 
  void trace();  ///< trace light through a complete system
  void init(Light* l, LowLevelSystem* s);	  ///< init the interactions based on light model
  void computeElementDiameters(Ray* light, OpticalSystem* system); ///< compute all "Automatic" Diameters to let the marginal ray (!) through
			       
  RayAiming* mRayAiming;         ///< methods and data for handling RayAiming 
  Interaction* mInteraction;   ///< This is used for handling interactions

 protected:
  //  Propagation mPropagation;  ///< This is used for handling propagations
  Light* mLight;                 ///< Pointer to light to be traced
  LowLevelSystem* mSystem;       ///< Pointer to the optical system
};

#endif
