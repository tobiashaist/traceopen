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
///  Elements will have a boundingGeometry (Box) which we need for
///  non-sequential tracing things
///
///  Within an Element we (most often) will have sequential tracing
///  and the user will say which SubElements (stored in mSubElements) will
///  be interacted with after each other and which leading
///  interaction should be followed.
///  But: This order of SubElements will depend of the first Subelement
///  that will be hit by the light.
///  Therefore, if we have N SubElements we will need N x N entries
///  (that's the most general case)
///  and later re will write some code that help us to automatically
///  create and fill this list.
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
// TODO: BoundingKram
// TODO: mElementOrder to be filled

class Element
{
  
public:
  Element();			///< ctor
  Element(const Element& element);	///< copy ctor
  virtual ~Element();		///< dtor

  void swap(Element& element);                   ///< swap operation
  virtual void show();				 ///< just for debugging purposes
  Element& operator=(Element& element);          ///< assignment OP
  
  std::unique_ptr<Element> mSmartPtrElement; // just very short in use (see above for explanation)

  virtual Element* copy(bool deep = true);      ///< creates and copies
  virtual void callInteraction(Tracing* trace, Light* light);

  Point* getPosition();                      ///< get the Posiiton of the surface
  Direction* getOrientation();               ///< get the Posiiton of the surface

  void standardLens(real r1, real r2,
		    real thickness, Material* material,
		    real diameter = 0);   ///< create a standard lens
  void achromat(real r1, real r2, real r3,
		real thickness1, real thickness2,
		Material* m1, Material*  m2,
		real diameter = 0);      ///< create an achromat

  void addSubElement(Element* const e,  Material* const m);
  int getCntSubElements() {return mSubElements.size();}
  Element* getElement(int nr);
    
 // ---------------------------------------------------
  int mInternalElementIndex;
 protected:
  
  Point mPosition;		///< Position in Space (global coordinates)
  Direction mOrientation;	///< orientation in Space (global coordinates)

  Material* mSurroundingMaterial;  // Pointer to the surroundingMaterial
  
  std::vector<Element*> mSubElements;  ///< The Element consists of SubElements 
  std::vector<std::vector<int>> mElementOrder;  ///< gives the order of the SubElements for tracing 
  
  Parameter<real> mWeight;	///< Weight of element in g
  Parameter<real> mPrice;	///< Price of element in Euro
  std::unique_ptr<JonesMatrix>  mJonesMatrix;    ///< Pointer to a Jones Matrix or NULL

};

#endif
