////////////////////////////////////////////////////////////
/// \file refractionwaves.cc
/// \brief class RefractionRays
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "refractionwaves.h"
#include "logging.h"



//////////////////////////////////////////////////////////////////////
/// \param light light to be traced through. Beware: SHOULD BE waves
/// \param element  the element we wish to trace through. 
//////////////////////////////////////////////////////////////////////
void RefractionWaves::perform(Light* light, Element* const element)
{
  LOG("Perform for RefractionWave");
}


