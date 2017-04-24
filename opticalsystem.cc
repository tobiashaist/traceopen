////////////////////////////////////////////////////////////
/// \file opticalsystem.cc
/// \brief class OpticalSystem
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "opticalsystem.h"

////////////////////////////////////////////////////////////
/// \param e Pointer to Element to be added to end of list
////////////////////////////////////////////////////////////
void OpticalSystem::addElement(Element * const  e)
{
  mElements.push_back(e);
}

////////////////////////////////////////////////////////////
OpticalSystem::OpticalSystem() : mElements(10)
{
  ;
}

////////////////////////////////////////////////////////////
/// \param nr index (0 ... size) of element of the optical system
/// \return  Pointer to Element number nr
////////////////////////////////////////////////////////////
Element* const OpticalSystem::getElement(const int nr) const
{
  return mElements[nr];
}

////////////////////////////////////////////////////////////
/// \param nr index (0 ... size) of element of the optical system
/// \param  Pointer to Element number nr
/// \return -1 if index is out of bounds, otherwise: nr
////////////////////////////////////////////////////////////
int OpticalSystem::setElement(Element* const e, const int nr)
{
  if(nr > mElements.size())
    return -1;

  mElements[nr] = e;
  return nr;
}
