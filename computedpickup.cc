////////////////////////////////////////////////////////////
/// \file computedpickup.cc
/// \brief class Computed
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "computedpickup.h"


//////////////////////////////////////////////////////////////////////
/// \param tracing Tracing in order to have Light and System
//////////////////////////////////////////////////////////////////////
ComputedPickup::ComputedPickup(Tracing* tracing,  typePickup type, Parameter<real>* p1,
			       Parameter<real>* p2, real offset, real multiplier,
			       real constant3, real constant4) :
  Computed(tracing), mType(type), mP1(p1), mP2(p2), mOffset(offset),
  mMultiplier(multiplier), mConstant3(constant3), mConstant4(constant4)
{
}

//////////////////////////////////////////////////////////////////////
/// \param tracing Tracing in order to have Light and System
//////////////////////////////////////////////////////////////////////
void ComputedPickup::compute()
{
  switch(mType)
    {
    case typePickupLinear:
      break;
    }

}
