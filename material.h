////////////////////////////////////////////////////////////
/// \file material.h
/// \brief include file for class Material
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef MATERIAL_HPP 
#define MATERIAL_HPP

#include <complex>
#include <string>
#include "basicdefinitions.h"
#include "parameter.h"
#include "environment.h"


////////////////////////////////////////////////////////////
///  \brief Material is an abstract base calls that represents all Materials  
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
class Material
{
  
public:

  explicit Material(std::string name, Environment* env=0, real specificicWeight=0);  ///< ctor
  virtual ~Material();			///< dtor
  virtual real getRefractiveIndex(real wavelength,
				 std::complex<real> ex, std::complex<real> ey,
				  std::complex<real> ez) = 0;  ///< get refractiveIndex
  std::string& getName();      ///< get the Name of the Material
  
 protected:
  std::string mName;			///< name of Material
  Parameter<real> mSpecificWeight;	///< Dispersion
  Environment* mEnvironment;            ///< Enviromental conditions (e.g. Temperature)
};

#endif
