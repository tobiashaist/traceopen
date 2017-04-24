////////////////////////////////////////////////////////////
/// \file tracing.h
/// \brief include file for class Tracing
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef TRACING_HPP 
#define TRACING_HPP

#include "basicdefinitions.h"
#include "interaction.h"
#include "light.h"
#include "opticalsystem.h"

#include <iostream>

////////////////////////////////////////////////////////////
///  \brief Most optical components are made out of Surfaces
////////////////////////////////////////////////////////////
///  
///  ///  
///  The abstract base class Tracing is the main container for 
///  propagation and interaction.
///
///  \date 15.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Tracing 
{
  
public:
  Tracing();			///< ctor
  ~Tracing();			///< dtor 
  void setInteraction(Interaction*  i);   ///< set the interation to i
  void trace(Light* l, OpticalSystem* s) const;  ///< trace light through a complete system
  void init(Light* const l);	  ///< init the interactions based on light model
	     
protected:
  //  Propagation* mPropagation;    ///< This is used for handling propagations
  Interaction* mInteraction;    ///< This is used for handling interactions
};

#endif
