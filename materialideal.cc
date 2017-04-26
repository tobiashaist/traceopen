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

#include "materialideal.h"



////////////////////////////////////////////////////////////
/// \param n refractive index
////////////////////////////////////////////////////////////
MaterialIdeal::MaterialIdeal(const std::string name,
			     Environment* env, real n, real dispersion,
			     real absorption) :
  Material(name, env, 0), mN(n), mDispersion(dispersion)
{
}


////////////////////////////////////////////////////////////
/// \param wavelength wavelength in m
/// \param ex polarization electrical field in x direction in global coordinates
/// \param ey polarization electrical field in x direction in global coordinates
/// \param ez polarization electrical field in x direction in global coordinates
////////////////////////////////////////////////////////////
					       
real MaterialIdeal::getRefractiveIndex(real wavelength, 
				       std::complex<real> ex, std::complex<real> ey,
				       std::complex<real> ez)
{
  return mN.get();
}
