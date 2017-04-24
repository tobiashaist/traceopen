////////////////////////////////////////////////////////////
/// \file refractionrays.cc
/// \brief class RefractionRays
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "refractionrays.h"
#include "traceopenerror.h"
#include <iostream>
#include "logging.h"
using namespace std;


//////////////////////////////////////////////////////////////////////
/// \param light light to be traced through. Beware: SHOULD BE Rays
/// \param element  the element we wish to trace through. 
//////////////////////////////////////////////////////////////////////
void RefractionRays::perform(Light* light, Element* const element)
{
  // Todo: assert for rays
  LOG("RefractionRays");
  throw TraceOpenError("Test", 3);

}
