////////////////////////////////////////////////////////////
/// \file material.cc
/// \brief class Material (abstract base class)
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "material.h"



////////////////////////////////////////////////////////////
/// \param n refractive index
////////////////////////////////////////////////////////////
Material::Material(std::string name, Environment* env, real specificWeight) :
  mName(name), mEnvironment(env), mSpecificWeight(specificWeight)
{
}

////////////////////////////////////////////////////////////
/// \param n refractive index
////////////////////////////////////////////////////////////
Material::~Material() 
{
}

					       

