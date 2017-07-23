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
  LOG("Element::ctor with index", mInternalElementIndex);
  // Beware: on construction a Jones matrix is not necessarily created
}

////////////////////////////////////////////////////////////
/// copy ctor
/// \param element Element 
////////////////////////////////////////////////////////////
Element::Element(const Element& element) 
{
  mInternalElementIndex = ++gInternalElementIndex;
  LOG("Element::ctor with index", mInternalElementIndex);
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
  LOG("Element::dtor");
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
Element* Element::copy() 
{
  LOG("Element::copy");

  mSmartPtrElement.reset(new Element(*this)); // here we generate
  // a new Element and the mSmartPtrElement gets Ownership for that

  LOG("Element::copy teil 2");
  return mSmartPtrElement.get();

    // Here something suitable should/could be used !
  // actually a deep copy !
}

////////////////////////////////////////////////////////////
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
Element& Element::operator=(Element& element) 
{
  Element temp(element);
  swap(element);
  return* this;
}

//////////////////////////////////////////////////////////////////////
void Element::callInteraction(const Tracing* trace, Light* light)
{
  LOG("callInteraction Element");
}

////////////////////////////////////////////////////////////
/// just for debugging
////////////////////////////////////////////////////////////
void Element::show()
{
  LOG("Element::show having subelements: ", getCntSubElements(), mInternalElementIndex);
  LOG(" .... now showing the content: ");
  for(int t=0; t < getCntSubElements(); t++)
    mSubElements[t]->show();
  LOG(" ---- DONE showing element ");
}

////////////////////////////////////////////////////////////
/// \param element element to be swapped with this object
////////////////////////////////////////////////////////////
void Element::swap(Element& element) 
{
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
//////////////////////////////////////////////////////////////////////
void Element::standardLens(real r1, real r2, real thickness,
				       Material* const material, real diameter)
{
  LOG("Element::standardLens");
  SurfaceSpherical* s = new SurfaceSpherical(r1, diameter, Point(0,0,0));
  addSubElement(s, material);

  //  s = new SurfaceSpherical(r2, diameter, Point(0,0,thickness));
  //  LOG("Thickness = ", thickness);
  //  addSubElement(s, material);
  LOG("Element::standardLens exit");
  show();
}

//////////////////////////////////////////////////////////////////////
/// \param s Pointer to surface
/// \param m Pointer to material
//////////////////////////////////////////////////////////////////////
void Element::addSubElement(Element* const e,  Material* const m)
{
  LOG("Element::addSubElement");
  Element* sc = e->copy();   // Copy of the Element is generated and ownership has
                             // sc->mSmartPtrSurface
  LOG("Element::addSubElement done copy");
  mSubElements.push_back(move(sc->mSmartPtrElement));  

  LOG("Element::addSubElement done pushback");
  // TODO  mMaterials.push_back(m);
}


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
  SurfaceSpherical* s = new SurfaceSpherical(r1, diameter, Point(0,0,0));
  addSubElement(s,m1);

  s = new SurfaceSpherical(r2, diameter, Point(0,0,thickness1));
  addSubElement(s,m2);

  s = new SurfaceSpherical(r3, diameter, Point(0,0,thickness2));
  addSubElement(s,m2);
}

//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
/// \return a pointer to the desired Element
//////////////////////////////////////////////////////////////////////
Element* Element::getElement(int number)
{
  ELOG("Element::getElement",number);

  return mSubElements[number].get();
}
