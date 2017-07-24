////////////////////////////////////////////////////////////
/// \file element.h
/// \brief include file for class Element
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef ELEMENT_HPP 
#define ELEMENT_HPP

#include "basicdefinitions.h"
#include "light.h"
#include "parameter.h"
#include "jonesmatrix.h"
#include "direction.h"
#include "material.h"
class Surface;


class Tracing;

#include <iostream>
#include <memory>
#include <vector>


////////////////////////////////////////////////////////////
///  \brief Element represents an element/component of an optical system  
////////////////////////////////////////////////////////////
///  
///  In TraceOpen Elements are the building blocks of optical systems. 
///  A typical element might be a lens which might consist of
///  multiple surfaces.
///  An element might also be a "group" of lenses or other
///  things like a scattering volume.
///  But even the volume has boundaries .... which are then surfaces
///
///  The Surface has always a Medium on the left side and on the right side
///
///  Most important: The Element itself consists of Elements ... and
///  a special case of Elements are surfaces
///
///  Elements might have a boundingGeometry (Box) which we might need for
///  non-sequential tracing things (but we can also do by hand ... we will see)
///
///  For the tracing we will only trace through elements without subelements
///  For that the OpticalSystem consisting of Elements will be first converted
///  to a LowLevelSystem which consists of Elements (without subElements).
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////

class Element
{
public:
  explicit Element(Element* parent = NULL);      ///< ctor
  Element(const Element& element);	         ///< copy ctor
  virtual ~Element();		                 ///< dtor

  void swap(Element& element);                   ///< swap operation
  Element& operator=(Element& element);          ///< assignment OP
  virtual Element* copy(bool deep = true);       ///< creates and copies
  
  virtual void show();				 ///< just for debugging purposes

  virtual void callInteraction(Tracing* trace, Light* light);

  void setPosition(real x, real y, real z);  ///< Position relativ to ParentElement
  void setOrientation(real alpha, real beta, real gamma);  ///< orientation relativ to Par
  Point* getPosition();                      ///< get the Posiiton of the surface
  Direction* getOrientation();               ///< get the Posiiton of the surface
  void addSubElement(Element* const e,  Material* const m);
  int getCntSubElements() {return mSubElements.size();}
  Element* getElement(int nr);               ///< get subElement nr
  void setWeight(real weight);		     ///< set the weight in g
  real getWeight();		             ///< get the weight in g
  void setPrice(real price);		     ///< set the price in Euro
  real getPrice();		             ///< get the price in Euro
  void setMaterials(Material* m1, Material* m2); ///< set the materials
  Material* getMaterialLeft();			 ///< get the left material
  Material* getMaterialRight();			 ///< get the left material
  
  void standardLens(real r1, real r2,
		    real thickness, Material* material,
		    real diameter = 0);   ///< create a standard lens
  void achromat(real r1, real r2, real r3,
		real thickness1, real thickness2,
		Material* m1, Material*  m2,
		real diameter = 0);      ///< create an achromat

 // ---------------------------------------------------
  int mInternalElementIndex;   ///< for internal bookkeeping (but not really used)

 protected:
  Element*  mParent;    ///< we need that for the relative position/orientation
  Point mPosition;		///< Position in Space (global coordinates)
  Direction mOrientation;	///< orientation in Space (global coordinates)
  Material* mMaterialLeft;      ///< The Material left of surface
  Material* mMaterialRight;     ///< The Material right of surface

  std::vector<Element*> mSubElements;  ///< The Element (might) consist of SubElements 
  std::vector<std::vector<int>> mElementOrder;  ///< gives the order of the SubElements for tracing 
  
  Parameter<real> mWeight;	///< Weight of element in g
  Parameter<real> mPrice;	///< Price of element in Euro
  std::unique_ptr<JonesMatrix>  mJonesMatrix;    ///< Pointer to a Jones Matrix or NULL

};

#endif
