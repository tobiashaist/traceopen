////////////////////////////////////////////////////////////
/// \file paraxiallens.cc
/// \brief class ParaxialLens
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "paraxiallens.h"
#include "surfacespherical.h"
#include "logging.h"
#include "tracing.h"

//////////////////////////////////////////////////////////////////////
/// ctor
//////////////////////////////////////////////////////////////////////
ParaxialLens::ParaxialLens(real f) 
{
  ELOG("ParxialLens::ctor");
  mFocalLength.set(f);
}


//////////////////////////////////////////////////////////////////////
/// dtor
//////////////////////////////////////////////////////////////////////
ParaxialLens::~ParaxialLens()
{
  ELOG("ParxialLens::dtor");
}

//////////////////////////////////////////////////////////////////////
ParaxialLens::ParaxialLens(ParaxialLens& lens) 
{
  ELOG("ParaxialLens::COPY CTOR");
  mFocalLength.set(lens.mFocalLength.get());
}

//////////////////////////////////////////////////////////////////////
/// \return Pointer to the element which has been newly created (and copied)
/// We need that for addElement within OpticalSystem
//////////////////////////////////////////////////////////////////////
ParaxialLens* ParaxialLens::copy()
{
  ELOG("ParaxialLens::copy");
  ParaxialLens* l = new ParaxialLens(*this); // here we generate
  return l;
}

//////////////////////////////////////////////////////////////////////
Direction ParaxialLens::computeSurfaceNormal(Point& p)
{
  // Todo: Was sinnvolles !
  
  real a =0;
  real b =0;
  real c =1;
  
  return(Direction(a,b,c));
}

//////////////////////////////////////////////////////////////////////
void ParaxialLens::callInteraction(const Tracing* trace, Light* light)
{
  ELOG("ParaxialLens::callInteraction ParaxialLens");
  trace->mInteraction->interactParaxialLens(light, this);
}


////////////////////////////////////////////////////////////
/// just for debugging
////////////////////////////////////////////////////////////
void ParaxialLens::show()
{
  LOG("SHOW ParaxialLens", mInternalElementIndex, mFocalLength.get());
}



////////////////////////////////////////////////////////////
/// assignment operator
/// \param element element to be assigned to this ParaxialLens
////////////////////////////////////////////////////////////
ParaxialLens& ParaxialLens::operator=(ParaxialLens& element) 
{
  ELOG("ParaxialLens::operator=");
  ParaxialLens temp(element);
  swap(element);
  return* this;
}

////////////////////////////////////////////////////////////
/// \param element element to be swaped with this ParaxialLens
////////////////////////////////////////////////////////////
void ParaxialLens::swap(ParaxialLens& element) 
{
  ELOG("ParaxialLens::swap");
  std::swap(mFocalLength, element.mFocalLength);
}


////////////////////////////////////////////////////////////
/// \param element element to be swaped with this ParaxialLens
////////////////////////////////////////////////////////////
void ParaxialLens::setFocalLength(real f) 
{
  mFocalLength.set(f);
}

