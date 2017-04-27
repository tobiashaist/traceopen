////////////////////////////////////////////////////////////
/// \file computed.h
/// \brief include file for class Computed
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef COMPUTED_HPP 
#define COMPUTED_HPP

#include "basicdefinitions.h"
#include "tracing.h"

#include <iostream>

////////////////////////////////////////////////////////////
///  \brief Computed manages the automatic computation of single parameters (Pickups, Solves)
////////////////////////////////////////////////////////////
///  
///  This is core class for handling things like pickups or solves ....
///  or more general: the automatic computation of single parameters based
///  on other quantities. This has to be distinguised from "optimization".  
///  During optimization we optimize the really free degrees of freedom
///  which we call "variables". 
///  Other parameters also change in the course of optimization but
///  these parameters can be (quite simply) computed out of all
///  other parameters of the system and the light  (including the 
///  variables.)
///  In Computed we store exactly one of these things.
///
/// The main (architectural) problem is, that for the actual computation
/// of the things we typically have to somehow trace light through the
/// system. This means we  need access to (if we want to be general) 
/// more or less everything (light, optical system, variants, general things ..) 
/// The best thing might be to run it always with some instance of "Tracing" ....
/// But I am not sure .....
/// 
/// Most classic computations (solves) can and will be computed based on
/// just one ray.
/// However, there are cases where this is not true, e.g. - most simple -
/// the diameter of the image field.
/// 
/// Therefore, it might be necessary for some of the computational routines
/// to get multiple Rays (even Lights ?) or specialized RayBundles in order
/// to their work.
/// The best interface for that is up till now not clear to me.... but critical!
/// 
/// First approach: We change "Tracing" so that it first just stores Light* and 
/// OpticalSystem* and the actual "trace" method then is called in order to
/// perform real tracing.
/// That way: Tracing would be also some sort of container for the definition
/// of a certain trace.
/// That way we might give as a Parameter a vector of Tracings to our
/// class computed and it would be up to the computation function at hand
/// to make best out of it.
/// Some would not expect one one entry (e.g. Pickups, where we only would use)
/// the OpticalSystem part of the Tracing.
/// Others (e.g. parxial solves) would also use the Ray definition of the Tracing
/// and other might use more complex things ....
///
/// Now ... anyway we have to think about where to put all the computations.
/// Version 1: We just put them here into this class (might become long)
/// Version 2: We make subclasses for different purposes (pickups, waves ...)
/// Version 3: functors or something similar.
///
/// I guess the best thing is to work with subclasses. We start with Pickups
///  \date 26.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Computed
{

public:
  Computed(Tracing* tracing);	///< ctor
  
protected:
  Tracing* mTracing;              ///< The Light (typically a Ray) and System used for the comput.
};

#endif
