////////////////////////////////////////////////////////////
/// \file surface.h
/// \brief include file for class Surface
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef SURFACE_HPP 
#define SURFACE_HPP

#include "basicdefinitions.h"
#include "point.h"
#include "direction.h"
#include "parameter.h"

#include <iostream>
#include <memory>


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
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

// We should include
// Coating
// BRDF
// Aperture
// SurfaceError

class Surface 
{
  
public:
  Surface(Point pos, Direction dir, real diameter); ///< ctor
  Surface(const Surface& surf);                           ///< copy ctor
  virtual ~Surface();                               ///< dtor
  virtual Surface* copy();   ///< copies the Surface and sets the pointer to mSmartPtrSurface
  std::unique_ptr<Surface> mSmartPtrSurface; // just very short in use (see above for expl.)
  
protected:

  Point mPosition;		///< Position in Space (global coordinates)
  Direction mOrientation;	///< orientation in Space (global coordinates)
  Parameter<real> mDiameter;	///< Diameter of usable surface (inner circle)

#if 0
  Aperture mAperture;          	///< Detailed specification of aperture
  Coating mCoating;		///< Coating of Surface
  BRDF mBRDF;			///< scattering contribution
  SurfaceError mSurfaceError;   ///< Surface deviation
#endif
};

#endif
