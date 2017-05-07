////////////////////////////////////////////////////////////
/// \file interaction.h
/// \brief include file for class Interaction
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 



#ifndef INTERACTIONMODEL_HPP 
#define INTERACTIONDODEL_HPP

#include "basicdefinitions.h"
#include "interaction.h"
#include <iostream>




////////////////////////////////////////////////////////////
///  \brief Here, all global interactions (used for tracing etc.)
///   are stored
////////////////////////////////////////////////////////////
///
///  \date 5.5.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

class InteractionModel 
{
  
public:
  void setGlobalInteractions( Light* light); ///< set global interactions according to light modell

  Interaction* mRefraction;	///< this is what we call when refraction occurs

 //  Reflection* mReflection;	///< this is what we call when refraction occurs  
};

#endif
