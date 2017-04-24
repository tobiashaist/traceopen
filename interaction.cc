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

#include "interaction.h"
#include "refractionrays.h"
#include "refractionwaves.h"
#include "traceopenerror.h"


//////////////////////////////////////////////////////////////////////
Interaction::Interaction() : mRefraction(NULL)
{
  ;
}

//////////////////////////////////////////////////////////////////////
Interaction::~Interaction()
{
  if(mRefraction != NULL)
    delete mRefraction;
}

//////////////////////////////////////////////////////////////////////
/// \param light light model to be used for global interactions
//////////////////////////////////////////////////////////////////////
void Interaction::setGlobalInteractions(Light* const light)
{   
  switch(light->getType())
    {
    case typeLightRay:
      mRefraction = new RefractionRays;
      break;
    case typeWaveScalar:
      mRefraction = new RefractionWaves;
      break;
    default:
      throw TraceOpenError("wrong light type inf setGlobalInteraction", 0);
    }
}

