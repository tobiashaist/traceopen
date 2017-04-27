////////////////////////////////////////////////////////////
///     \file opticalsystem.h
///  \brief include file for class Surface
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef OPTICALSYSTEM_HPP 
#define OPTICALSYSTEM_HPP

#include "basicdefinitions.h"
#include "element.h"
#include "parameter.h"
#include "surface.h"

#include <vector>
#include <iostream>


// TODO
// Variants

////////////////////////////////////////////////////////////
///  \brief Describes the complete optical system
////////////////////////////////////////////////////////////
///  
///  We trace light through optical systems. During the trace different
///  components are encountered by the light. These things are handled
///  in the propagation and interaction classes. 
///  However, the hardware of the whole optical system (consisting of
///  lenses, surfaces, materials etc. is stored and managed in this class
///  (and the important subclass Element). 
///
///  Mainly the optical system consists of Elements (and additional information)
///  And of course, Elements consist of Surfaces, Materials, Coatings etc.
///
///  The class never creates or destructs elements (or surfaces)
///  (otherwise we would have to use smartpointer or something similar)
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class OpticalSystem
{
  // Beware: We cannnot make the pointer Element* point to constant elements
  // because we cannot guarantee that these elements will not change.
  // During optimization they will change ...
  
public:
  OpticalSystem();
  int addElement(Element* e);     ///< add one Element at the end of the system
  int setElement(Element* e, int nr);	 ///< replace Element number n 
  Element* const getElement(int nr) const;       ///< set the Element number n

 protected:
  std::vector<Element*> mElements;     ///< Here, the elements are stored
  Parameter<double> mPrice;       ///< Price of the optical system
  // etc.
  Surface* mStop;                 ///< for classic optical design we need a stop SURFACE
};

#endif
