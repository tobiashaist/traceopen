////////////////////////////////////////////////////////////
/// \file surfacespherical.h
/// \brief include file for class SurfaceSpherical
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef SURFACESPHERICAL_HPP 
#define SURFACESPHERICAL_HPP

#include "basicdefinitions.h"
#include "surface.h"


#include <iostream>
#include "parameter.h"



////////////////////////////////////////////////////////////
///  \brief Most optical components are made out of Surfaces
////////////////////////////////////////////////////////////
///  
///  Most often, elements are lenses or mirrors. These elements are
///  "elements with (or consisting of) surfaces".
///  
///  The abstract base class Surface is the core for the implementation
///  of all kinds of surfaces.
///
///  \date 15.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

class SurfaceSpherical : public Surface
{
 public:
  SurfaceSpherical(real mRadius, real diameter, Point p); ///< ctor
  Parameter<real>* getRadiusPointer(); /// Pointer to the radius
  
protected:
  Parameter<real> mRadius;	///< Radius of curvature
};

#endif
