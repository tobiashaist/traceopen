////////////////////////////////////////////////////////////
///  \file lowlevelsystem.h
///  \brief include file for class Surface
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef LOWLEVELSYSTEM_HPP 
#define LOWLEVELSYSTEM_HPP

#include "opticalsystem.h"

#include <vector>
#include <iostream>
#include <memory>
////////////////////////////////////////////////////////////
///  \brief Describes the complete optical system on a surface basis
////////////////////////////////////////////////////////////
///
/// The standard description for optical systems (class OpticalSystem)
/// is not well suited for tracing rays in a non-sequential way through
/// it.
/// For this kind of tracing it is much better to have a simple (non-recursive)
/// surface-based description.
///
/// For the tracing it is therefore necessary to first convert the OpticalSystem
/// into the LowLevelSystem
///
/// For some rare elements we cannot describe based on surfaces.
/// Therefore, still we use the Element class for storing but do not
/// use here the subElements !
///
///  \date 22.7.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class LowLevelSystem
{
  
public:
  LowLevelSystem(); 		///< ctor
  Element* next();              ///< get the next Element (=surface)
  void reset();                 ///< reset
  void show();
  void convertTo(OpticalSystem* system); ///< fill the LowLevel description
  int getCntElements();    ///< the number of Elements=surfaces
  int getCurrentIndex();        ///< the index of the current surface
  Element* getElement(int index=-1);  ///< get Element. Without number: Take current
  void addElement(Element* e);  ///< add a surface to the System
  
protected:
  int mCurrentIndex;		///< Index of the current Element (=surface)
  int mNumberOfElements;

  std::vector<Element*> mElements; ///< Here, the elements are stored
  
  Surface* mStop;                 ///< for classic optical design we need a stop SURFACE
};

#endif
