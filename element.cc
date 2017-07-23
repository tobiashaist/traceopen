////////////////////////////////////////////////////////////
/// \file element.cc
/// \brief class Element
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "element.h"
#include "logging.h"
#include "surfacespherical.h"

int gInternalElementIndex = 0;   // mainly for debugging / testing

////////////////////////////////////////////////////////////
/// ctor
Element::Element() 
{
  mInternalElementIndex = ++gInternalElementIndex;
  ELOG("Element::ctor with index", mInternalElementIndex);

  // Beware: on construction a Jones matrix is not necessarily created
}

////////////////////////////////////////////////////////////
/// copy ctor
/// \param element Element 
////////////////////////////////////////////////////////////
Element::Element(const Element& element) 
{
  mInternalElementIndex = ++gInternalElementIndex;
  ELOG("Element::copy ctor with index", mInternalElementIndex);
  mWeight =  element.mWeight;
  mPrice = element.mPrice;
  if(mJonesMatrix.get() != NULL)
    {
      // TOOD: 1) create a new Jones matrix, 2) Deep Copy it
    }
}


////////////////////////////////////////////////////////////
/// dtor
////////////////////////////////////////////////////////////
Element::~Element() 
{
  ELOG("Element::dtor", mInternalElementIndex);
}

////////////////////////////////////////////////////////////
/// \return pointer to Position in space
////////////////////////////////////////////////////////////
Point* Element::getPosition()
{
  return &mPosition;
}


////////////////////////////////////////////////////////////
/// \return pointer to Position in space
////////////////////////////////////////////////////////////
Direction* Element::getOrientation()
{
  return &mOrientation;
}

////////////////////////////////////////////////////////////
// TODO: This is not really used for anything in this base class
// but it is necessary in the derived classes
////////////////////////////////////////////////////////////
Element* Element::copy(bool deep) 
{
  ELOG("Element::copy", mInternalElementIndex);
  Element* e = new Element (*this);

  // Here something suitable should/could be used !
  // actually a deep copy !

  return e;
}

////////////////////////////////////////////////////////////
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
Element& Element::operator=(Element& element) 
{
  ELOG("Element::operator=", mInternalElementIndex, element.mInternalElementIndex);
  Element temp(element);
  swap(element);
  return* this;
}

//////////////////////////////////////////////////////////////////////
void Element::callInteraction(Tracing* trace, Light* light)
{
  LOG("Element::callInteraction", mInternalElementIndex);
}

////////////////////////////////////////////////////////////
/// just for debugging
////////////////////////////////////////////////////////////
void Element::show()
{
  LOG("Element::show ", mInternalElementIndex); 
  LOG("Having subelements: ", getCntSubElements());
  for(int t=0; t < getCntSubElements(); t++)
    {
      LOG(" .... now showing the content for subelement ", t);
      mSubElements[t]->show();
    }

}

////////////////////////////////////////////////////////////
/// \param element element to be swapped with this object
////////////////////////////////////////////////////////////
void Element::swap(Element& element) 
{
  ELOG("Element::swap", mInternalElementIndex, element.mInternalElementIndex);
  std::swap(mWeight, element.mWeight);
  std::swap(mPrice, element.mPrice);
  std::swap(mJonesMatrix, element.mJonesMatrix);
}


//////////////////////////////////////////////////////////////////////
/// \param r1 radius of curvature surface 1
/// \param r2 radius of curvature surface 2
/// \param thickness thickness between surface 1 and 2
/// \param material Pointer to material 
/// \param diameter lens diameter
/// TODO: Wer ist eigentlich verantwortlich, um diese Surfaces, die
/// so schön mit new angelegt werden, irgendwann mal wieder zu löschen
/// (das war der ursprüngliche Sinn der Smart Pointers !!!)
//////////////////////////////////////////////////////////////////////
void Element::standardLens(real r1, real r2, real thickness,
				       Material* const material, real diameter)
{
  ELOG("Element::standardLens", mInternalElementIndex);
  SurfaceSpherical* s = new SurfaceSpherical(r1, diameter, Point(0,0,0));
  mSubElements.push_back(s);  
  //  addSubElement(s, material);
  LOG("-----------------------");
  s = new SurfaceSpherical(r2, diameter, Point(0,0,thickness));

  mSubElements.push_back(s);  
  //  addSubElement(s, material);
}

//////////////////////////////////////////////////////////////////////
/// Beachte: Das ist ein add mit Copy Funktionalität !!!!
/// Vorsicht: Gut überlegen, ob ohne nicht besser ist !
//////////////////////////////////////////////////////////////////////
void Element::addSubElement(Element* const e,  Material* const m)
{
  ELOG("Element::addSubElement",getCntSubElements(), mInternalElementIndex, e->mInternalElementIndex);
  Element* sc = e->copy();   
  mSubElements.push_back(sc);  

  // TODO  mMaterials.push_back(m);
}


// TODO: Materialien fehlen noch komplett !!!

//////////////////////////////////////////////////////////////////////
/// \param r1 radius of curvature surface 1
/// \param r2 radius of curvature surface 2
/// \param r3 radius of curvature surface 3
/// \param thickness1 thickness between surface 1 and 2
/// \param thickness2 thickness between surface 2 and 3
/// \param m1 Pointer to material 1
/// \param mw Pointer to material 2
/// \param diameter lens diameter
//////////////////////////////////////////////////////////////////////
void Element::achromat(const real r1, const real r2, const real r3,
				   const real thickness1,
				   const real thickness2, Material* const m1,
				   Material* const m2,
				   const real diameter)
{
  ELOG("Element::achromat", mInternalElementIndex);
  SurfaceSpherical* s = new SurfaceSpherical(r1, diameter, Point(0,0,0));
  mSubElements.push_back(s);  
  //  addSubElement(s,m1);

  s = new SurfaceSpherical(r2, diameter, Point(0,0,thickness1));
  mSubElements.push_back(s);  
  //  addSubElement(s,m2);

  s = new SurfaceSpherical(r3, diameter, Point(0,0,thickness2));
  mSubElements.push_back(s);  
  //  addSubElement(s,m2);
}

//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
/// \return a pointer to the desired Element
//////////////////////////////////////////////////////////////////////
Element* Element::getElement(int number)
{
  ELOG("Element::getElement",number);

  return mSubElements[number];
}
