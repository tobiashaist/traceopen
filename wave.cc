////////////////////////////////////////////////////////////
/// \file wave.cc
/// \brief class Wave
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "wave.h"
#include "logging.h"


Wave::Wave() : Light(typeWaveScalar, 633e-9, 1)
{

  ;
}


////////////////////////////////////////////////////////////
void Wave::show() 
{
  LOG("Light = Wave");
}
