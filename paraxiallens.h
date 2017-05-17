////////////////////////////////////////////////////////////
/// \file paraxiallens.h
/// \brief include file for class ParaxialLens
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef PARAXIALLENS_HPP 
#define PARAXIALLENS_HPP

#include "basicdefinitions.h"
#include "element.h"
#include "point.h"

class Tracing;


#include <iostream>
#include <vector>


////////////////////////////////////////////////////////////
///  \brief ParaxialLens represents an ideal thin lens
////////////////////////////////////////////////////////////
///  
///  \date 16.5.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class ParaxialLens : public Element
{
  
public:
  ParaxialLens(real f=0);
  ParaxialLens(ParaxialLens& element); ///< copy ctor
  void swap(ParaxialLens& element);                   ///< swap operation
  ParaxialLens& operator=(ParaxialLens& element); ///< assignment OP
  virtual ParaxialLens* copy();         ///< deep copy the current lens and set smart ptr
  
  ~ParaxialLens();	///< dtor
  virtual void callInteraction(const Tracing* trace, Light* light);

  int getCntSurfaces();                   ///< return the number of surfaces
  void show();                       ///< just for debugging
  real getFocalLength();                  ///< return the focal length
  void setFocalLength(real f);            ///< sets the focal length

 protected:
  Parameter<real> mFocalLength;           ///< focalLength

};

#endif
