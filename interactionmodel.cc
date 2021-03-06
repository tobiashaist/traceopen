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

#include "interactionmodel.h"
#include "refractionrays.h"
#include "refractionwaves.h"
#include "traceopenerror.h"

// TODO: I guess we do not need that anymore

//////////////////////////////////////////////////////////////////////
/// \param light light model to be used for global interactions
//////////////////////////////////////////////////////////////////////
void InteractionModel::setGlobalInteractions(Light* const light)
{   
  ELOG("setGlobalInteractions");

  switch(light->getType())
    {
    case typeLightRay:
      mRefraction.reset(new RefractionRays);
      ELOG("Done RefractionRays ctor");
      
      break;
    case typeWaveScalar:
      mRefraction.reset(new RefractionWaves);
      break;
    default:
      throw TraceOpenError("wrong light type inf setGlobalInteraction", 0);
    }
}
