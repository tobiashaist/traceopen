////////////////////////////////////////////////////////////
/// \file raybundle.h
/// \brief include file for class RayBundle
///  \date 27.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef RAYBUNDLE_HPP 
#define RAYBUNDLE_HPP

#include "basicdefinitions.h"
#include "point.h"
#include "direction.h"
#include "ray.h"
#include "lightbundle.h"

#include <iostream>
#include <vector>

enum typeRayBundlePattern {typeRayBundlePatternRings, typeRayBundlePatternRectangular};
		   
////////////////////////////////////////////////////////////
///  \brief RayBundle manages Bundles of Rays
////////////////////////////////////////////////////////////
///  
/// The definition of the raybundle is not easy at all.  
/// We might have a generalized cone with different angles for
/// x and y direction and - even worse - these main axis
/// might of course be directed into other direction and
/// of course the are centered around another direction
/// (not necessarily the z-axix !)
///
/// And: The extension in practice is most of time given
/// according to the pupil of the optical system
/// Therefore, rayaiming has to be taken into account ....
///
/// Definitely ... the decision about which rays should
/// be started to be traced is a complicated one.
/// Therefore, we will make available different methods
/// that generate Rays.
///
/// We start with something simple.
///
/// Also, we do not mix this generation with RayAiming
/// (which needs access to the optical system and the light)
/// because that would make everything too much dependent.
/// Therefore the normal way is to first compute by RayAiming
/// one (or some) marginal rays and then these rays are used
/// as inputs for the generator here in this class.
///
///  \date 27.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class RayBundle : public LightBundle
{

public:
  RayBundle( ); ///< ctor
  void generateCone(int numberOfRays, real wavelength, real intensity,
		    typeRayBundlePattern pattern, Point* const p,
		    Direction* const dir, real angle); ///< generate a cone of light
  
};

#endif
