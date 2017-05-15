////////////////////////////////////////////////////////////
/// \file light.h
/// \brief include file for class Light
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef LIGHT_HPP 
#define LIGHT_HPP

#include "basicdefinitions.h"
#include "parameter.h"
#include "point.h"

#include <iostream>

////////////////////////////////////////////////////////////
///  \brief The abstract class light is the base class for all our light models
////////////////////////////////////////////////////////////
///  
///  Different models of light are used in optics. Most often, optical design can
///  be successfully achieved using the geometrical model based on rays.
///  However, for some applications we want to be able to use completely different
///  models. It is obvious that sometimes some sort of wave optics (scalar or
///  vectorial) is necessary. Even for these, different formulations are possible.
///  In addition, sometimes even more uncommen approaches (e.g. path integrals)
///  are feasible.
///
///  Up till now, we only implement ray-based simulations. But Traceopen should be
///  easily extensible to other light models. This is why the whole structure is
///  already prepared to handle other models.
///  "Light" is the base class for our light models. The class "Ray" e.g. is derived
///  from Light.
///
///  Polarization: In general, simulation using polarization is more complicated than
///  going without it (not matter if waves or rays).
///  We have different options to reflect this in the code.
///  Version 1: Subclasses (e.g. RayPolarized)
///  Version 2: Strategy pattern (having in Ray a point to a "Polarization" subclass
///     (but actually there are only two different variants ... with and without).
///     Therefore, the cost associated with it, I guess, is not worth it.
///  Version 3: Just straight forward definition of a flag (mUsesPolarization)
///   and based on this flag the methods in interaction (and perhabs propagation)
///   change their behavior.
///
///  The last version is - I think - the most simple and straight forward way to go.
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

enum typeLight {typeLightRay, typeWaveScalar, typeWaveVectorial, typeGaussian};

class Light {

public:
  Light(typeLight type, real lambda, real intensity);  ///< ctor
  virtual ~Light()  = 0;     ///< dtor
  void setPosition(Point p);    ///< sets the startposition of the light
  typeLight getType() const {return mLightType;}
  bool isAlive() const;	        ///< true -> Light is still alive (not vignetted)
  bool isUsingPolarization() const; /// true -> we should use polarization
  void setUsingPolarization(bool); ///< set/unset the usage of polarization
  
protected:
  typeLight mLightType;		///< what kind of Light (subclass)
  Parameter<real> mLambda;			///< Wavelength in m
  Parameter<real> mCoherenceLength;	///< coherence length in m
  Parameter<real> mIntensity;		///< power per m^2 = intensity in W/m^2
  Parameter<real> mOPD;			///< optical path difference
  bool mAlive;				///< true -> light still alive
  bool mUsesPolarization;		///< true -> we should use polarization
};

#endif
