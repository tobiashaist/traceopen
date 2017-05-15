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

class Tracing;

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
///  Here, it is clear that the class OWNs the surfaces.
///  Therefore, if we want (in general) access them
///  (e.g. we first created an achromat and later want to change the
///  radius of the third surface) we have to really do it by getting
///  a pointer to the surface and the call the set function
///  for that surface
/// 
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class ElementWithSurfaces : public Element
{
  
public:
  ElementWithSurfaces();	///< ctor
  ElementWithSurfaces(ElementWithSurfaces& element); ///< copy ctor
  
  ~ElementWithSurfaces();	///< dtor
  void swap(ElementWithSurfaces& element);                   ///< swap operation
  ElementWithSurfaces& operator=(ElementWithSurfaces& element); ///< assignment OP
  void callInteraction(const Tracing* trace, Light* light);

  virtual ElementWithSurfaces* copy();         ///< deep copy the current lens and set smart ptr
  
  void addSurface(Surface* s, Material*  m);  ///< add a surface at the end of mSurfaces
  void standardLens(real r1, real r2,
		    real thickness, Material* material,
		    real diameter = 0);   ///< create a standard lens
  void achromat(real r1, real r2, real r3,
		real thickness1, real thickness2,
		Material* m1, Material*  m2,
		real diameter = 0);      ///< create an achromat
  Surface* getSurface(int surfacenr);    ///< get a pointer to the surface
  Material* getMaterial(int surfacenr);  ///< get a pointer to the material
  real getZPosition(int surfacenr);      ///< get the z position of the surface
  int getCntSurfaces();                  ///< return the number of surfaces
  
  void show();                           ///< just for debugging
  
 protected:
  int mCntSurfaces;	   	        ///< number of surfaces
  
  std::vector<std::unique_ptr<Surface>> mSurfaces; ///< All surfaces that make the element

  // Here we have an important question. Should the materials also be owned by
  // the element ? Or should they stored just globally in the MaterialsDatabase
  // so that we just have to use ordinary pointers to them.
  // In principle in most cases, this database approach is the right thing.
  // However: When optimizing materials then, it is not so perfect.
  // Anyway, I think the database approach is more logically than the
  // way to always copy the material.
  
  std::vector<Material*> mMaterials; ///< Material between successive surfaces
};

#endif
