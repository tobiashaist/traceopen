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
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

enum typeLight {typeLightRay, typeWaveScalar, typeWaveVectorial, typeGaussian};

class Light {

public:
  Light(typeLight type, real lambda, real intensity);  ///< ctor
  void setPosition(Point p);    ///< sets the startposition of the light
  typeLight getType() const {return mLightType;}
  bool isAlive() const;	        ///< true -> Light is still alive (not vignetted)
  
protected:
  typeLight mLightType;		///< what kind of Light (subclass)
  Parameter<real> mLambda;			///< Wavelength in m
  Parameter<real> mCoherenceLength;	///< coherence length in m
  Parameter<real> mIntensity;		///< power per m^2 = intensity in W/m^2
  Parameter<real> mOPD;			///< optical path difference
  bool mAlive;				///< true -> light still alive
};

#endif
