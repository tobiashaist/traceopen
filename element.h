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

#include <iostream>
#include <memory>


////////////////////////////////////////////////////////////
///  \brief Element represents an element/component of an optical system  
////////////////////////////////////////////////////////////
///  
///  In TraceOpen Elements are the building blocks of optical systems. 
///  A typical element might be a lens which might consist of
///  multiple surfaces.
///  An element might also be a "group" of lenses or other
///  things like a scattering volume.
///  
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Element
{
  
public:
  Element();			///< ctor
  virtual ~Element();		///< dtor
  virtual Element* copy();      ///< copies the Element and sets the pointer to mSmartPtrElement
  std::unique_ptr<Element> mSmartPtrElement; // just very short in use (see above for explanation)
  
protected:

  Parameter<real> mWeight;	///< Weight of element in g
  Parameter<real> mPrice;	///< Price of element in Euro
  std::unique_ptr<JonesMatrix>  mJonesMatrix;    ///< Pointer to a Jones Matrix or NULL
};

#endif
