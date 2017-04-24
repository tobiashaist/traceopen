////////////////////////////////////////////////////////////
/// \file wave.h
/// \brief include file for class Wave (scalar wave)
/// \date 07.04.2017
/// \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef WAVE_HPP 
#define WAVE_HPP

#include "basicdefinitions.h"
#include "point.h"
#include "direction.h"
#include "light.h"

#include <iostream>

////////////////////////////////////////////////////////////
///  \brief Ray manages optical (polarized or unpolarized) Rays
////////////////////////////////////////////////////////////
///  
///  This is the basic class for representing light in a simple scalar waevoptical model.
///  The wave will be implemented with conventional Arrays and equidistant points
///  Other waveoptical methods should be derived from this class
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Wave: public Light
{

public:
  Wave();                          ///< std ctor

protected:

};

#endif
