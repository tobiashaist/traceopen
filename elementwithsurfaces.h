////////////////////////////////////////////////////////////
/// \file elementwithsurfaces.h
/// \brief include file for class ElementWithSurfaces
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef ELEMENTWITHSURFACES_HPP 
#define ELEMENTWITHSURFACES_HPP

#include "basicdefinitions.h"
#include "element.h"
#include "surface.h"
#include "material.h"
#include "point.h"

#include <iostream>
#include <vector>


////////////////////////////////////////////////////////////
///  \brief ElementWithSurfaces represents things like typical lenses  
////////////////////////////////////////////////////////////
///  
///  Most often, elements are lenses or mirrors. These elements are
///  "elements with (or consisting of) surfaces".
///  
///  We might in the future have elements with LOTS of surfaces, e.g. in
///  order to simulate quasi continuos changes.
///  Therefore, it would not be memory efficient to always have an
///  Array (of pointers) e.g. with 10.000 entries for every ElementWithSurfaces.
///  Therefore we use a container  ( vector<Surface*> )(
/// 
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class ElementWithSurfaces : public Element
{
  
public:
  ElementWithSurfaces();	///< ctor
  ~ElementWithSurfaces();	///< dtor
  void addSurface(Surface* s, Material*  m);  ///< add a surface at the end of mSurfaces
  void standardLens(real r1, real r2,
		    real thickness, Material* material,
		    real diameter = 0);   ///< create a standard lens
  void achromat(real r1, real r2, real r3,
		real thickness1, real thickness2,
		Material* m1, Material*  m2,
		real diameter = 0);      ///< create an achromat
		    
 protected:
  int mCntSurfaces;	   	        ///< number of surfaces
  
  std::vector<Surface*> mSurfaces;   ///< All surfaces that make the element

  std::vector<Material*> mMaterials; ///< Material between successive surfaces
};

#endif
