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

////////////////////////////////////////////////////////////
/// ctor
Element::Element() 
{
  // Beware: on construction a Jones matrix is not necessarily created
}

////////////////////////////////////////////////////////////
/// copy ctor
/// \param element Element 
////////////////////////////////////////////////////////////
Element::Element(const Element& element) 
{
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

}

////////////////////////////////////////////////////////////
// TODO: This is not really used for anything in this base class
// but it is necessary in the derived classes
////////////////////////////////////////////////////////////
Element* Element::copy() 
{
  // Here something suitable should/could be used !
  // actually a deep copy !

  return this;
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

////////////////////////////////////////////////////////////
/// just for debugging
////////////////////////////////////////////////////////////
void Element::show()
{
  LOG("SHOW ELEMENT");
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
