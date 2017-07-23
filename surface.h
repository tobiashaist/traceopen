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
#include "element.h"

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

class Surface : public Element
{
  
public:
  Surface(Point pos, Direction dir, real diameter); ///< ctor
  Surface(const Surface& surf);                     ///< copy ctor
  void swap(Surface& surface1);                     ///< swap operation
  virtual ~Surface();                               ///< dtor
  virtual Surface* copy(bool deep=true);   ///< copies the Surface and sets the pointer to mSmartPtrSurface
  Surface& operator=(Surface& surface);             ///< assignment operator

  virtual void show();
  virtual void callInteraction(Tracing* trace, Light* light);

  Point* getPosition();                      ///< get the Posiiton of the surface
  Direction* getOrientation();               ///< get the Posiiton of the surface
  Parameter<real>* getDiameter();            ///< get the Diameter
  
protected:
  int mInternalSurfaceIndex;
  Parameter<real> mDiameter;	///< Diameter of usable surface (inner circle)

#if 0
  Aperture mAperture;          	///< Detailed specification of aperture
  Coating mCoating;		///< Coating of Surface
  BRDF mBRDF;			///< scattering contribution
  SurfaceError mSurfaceError;   ///< Surface deviation
#endif
};

#endif
