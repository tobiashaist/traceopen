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
  LOG("COPY CTOR ParaxialLens ");
  mFocalLength.set(f);
}


//////////////////////////////////////////////////////////////////////
/// dtor
//////////////////////////////////////////////////////////////////////
ParaxialLens::~ParaxialLens()
{
  LOG("DTOR ParaxialLens");

}
//////////////////////////////////////////////////////////////////////
ParaxialLens::ParaxialLens(ParaxialLens& lens) 
{
  ELOG("COPY CTOR ParaxialLens");
  mFocalLength.set(lens.mFocalLength.get());
}

//////////////////////////////////////////////////////////////////////
/// \return Pointer to the element which has been newly created (and copied)
/// We need that for addElement within OpticalSystem
//////////////////////////////////////////////////////////////////////
ParaxialLens* ParaxialLens::copy()
{
  mSmartPtrElement.reset(new ParaxialLens(*this)); // here we generate
  // a new Element and the mSmartPtrElement gets Ownership for that
    
  return dynamic_cast<ParaxialLens*>(mSmartPtrElement.get());
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
  LOG("ParaxialLens::callInteraction ParaxialLens");
  trace->mInteraction->interactParaxialLens(light, this);
}


////////////////////////////////////////////////////////////
/// just for debugging
////////////////////////////////////////////////////////////
void ParaxialLens::show()
{
  Element::show();  // parent
  
  LOG("SHOW ParaxialLens");
}



////////////////////////////////////////////////////////////
/// assignment operator
/// \param element element to be assigned to this ParaxialLens
////////////////////////////////////////////////////////////
ParaxialLens& ParaxialLens::operator=(ParaxialLens& element) 
{
  ParaxialLens temp(element);
  swap(element);
  return* this;
}

////////////////////////////////////////////////////////////
/// \param element element to be swaped with this ParaxialLens
////////////////////////////////////////////////////////////
void ParaxialLens::swap(ParaxialLens& element) 
{
  std::swap(mFocalLength, element.mFocalLength);
}



////////////////////////////////////////////////////////////
/// \param element element to be swaped with this ParaxialLens
////////////////////////////////////////////////////////////
void ParaxialLens::setFocalLength(real f) 
{
  mFocalLength.set(f);
}

