////////////////////////////////////////////////////////////
/// \file materialideal.h
/// \brief include file for class MaterialIdeal
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef MATERIALIDEAL_HPP 
#define MATERIALIDEAL_HPP

#include <complex>
#include "basicdefinitions.h"
#include "parameter.h"
#include "environment.h"
#include "material.h"


////////////////////////////////////////////////////////////
///  \brief MaterialIdeal represents all ideal Materials  
////////////////////////////////////////////////////////////
///  
///  Subclasses have to derived
///  
///  
/// In the future we will derive classes (e.g. metamaterials) from this class.
/// However: We have to deeply think about the interface then !
///
/// Refractive Index and Reflection
// depend on 
/// - Wavelength
/// - Polarization
/// - Orientation of Material
/// 
/// We also need Subclasses for
/// - MaterialIdeal (perfect mirrors, Glass with given refractive index etc..) 
///
/// - Materials that need different equations for different spectral regimes
///
/// in General: we should have a look at optical material in General to
/// get the right (very general) interface
////////////////////////////////////////////////////////////
class MaterialIdeal : public Material 
{
  
public:
  MaterialIdeal(std::string name, Environment* env, real n,
		real dispersion=0, real absorption=0); ///< ctor

 virtual real getRefractiveIndex(real wavelength,
				 std::complex<real> ex, std::complex<real> ey,
				 std::complex<real> ez);
  
 protected:
  Parameter<real> mN;		///< refractive index
  Parameter<real> mDispersion;	///< Dispersion

};

#endif
