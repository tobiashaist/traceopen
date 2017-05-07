////////////////////////////////////////////////////////////
/// \file computedpickup.h
/// \brief include file for class ComputedPickup
///  \date 25.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef COMPUTEDPICKUP_HPP 
#define COMPUTEDPICKUP_HPP

#include "basicdefinitions.h"
#include "computed.h"

#include <iostream>

enum typePickup {typePickupLinear, typePickupQuadratic};

////////////////////////////////////////////////////////////
///  \brief ComputedPickup is a subclass of Computed and works for classical pickups
////////////////////////////////////////////////////////////
///  
///  This is core class for handling Pickups, a special case of "Computed"
///  computations.
/// 
///  \date 26.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class ComputedPickup : public Computed
{

public:
  ComputedPickup(Tracing* tracing, typePickup t, Parameter<real>* p1, Parameter<real>* p2,
		 real offset, real multiplier, real const3=0, real const4=0);	//< ctor
  void compute();				///< really do computation
  
protected:
  typePickup mType;             ///< Type of Computation (which equation);
  Parameter<real>* mP1;		///< Parameter 1, Beware mP1 points to an object which is not owned by this class
  Parameter<real>* mP2;		///< Parameter 2, Beware mP1 points to an object which is not owned by this class
  real mOffset;                 ///< Offset
  real mMultiplier;             ///< mMultiplier
  real mConstant3;              ///< for some other equations
  real mConstant4;              ///< for some other equations
  

};

#endif
