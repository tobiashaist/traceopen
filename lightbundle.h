////////////////////////////////////////////////////////////
/// \file lightbundle.h
/// \brief include file for class LightBundle
///  \date 27.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef LIGHTBUNDLE_HPP 
#define LIGHTBUNDLE_HPP

#include "basicdefinitions.h"
#include "point.h"
#include "direction.h"
#include "light.h"

#include <iostream>
#include <vector>


		   
////////////////////////////////////////////////////////////
///  \brief LightBundle manages Bundles of Rays and in general: "Arrays of light"
////////////////////////////////////////////////////////////
///  
/// We need LightBundles for three main reasons: 
/// 1) The user does not always has to do this by hand.
/// 2) To implement RaySplitting
/// 3) To trace efficiently (e.g. by GPU support) lots of light
///
/// Most often (99% of the cases) LightBundles mean RayBundles.
/// Actually, "LightBundle" is perhaps a bad name but it has been
/// chosen as a generalization of RayBundle for arbitrary
/// types of light. We need that (perhaps) for "LightSplitting" with waves
/// (because these, of course, are also reflected at interfaces).
///
/// We now discuss RaySplitting. Light propagates until it hits an interface
/// then, typically it gets reflected (or diffracted). Another part of the light
/// however will be reflected (and for diffration we might have multiple
/// additional orders). If the intensity of this additional light is above a certain
/// threshold, another ray (or wave) for this component will be generated.
///
/// Can this be used also for GPU based acceleration?
/// Yes. But we have to implement LightGPU, RayGPU and LightBundleGPU.
/// and of course we have to implement some conversion/transfer routines from
/// CPU to GPU for the light and the optical system (just to bring) them
/// efficiently for certain cases to the GPU.
///
/// 
///  \date 30.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class LightBundle 
{

public:
  LightBundle();
  
protected:
  int mCntLights;		      ///< number of Rays

  // It would be an option to use here again smart pointers
  // and to give ownership of these lights to mLights
  // we would, however have to copy all the rays
  // (compare our discussions in OpticalSystem with Elements)
  // We think that here, perform issues might really lead to
  // some problems when using smart pointers because
  // we definitely need LOTS of light.
  
  std::vector<Light*> mLights;         ///< the rays
};

#endif
