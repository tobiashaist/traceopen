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

#include "lowlevelsystem.h"
#include "logging.h"
#include "surfacespherical.h"
#include "materialideal.h"
#include "traceopenerror.h"
#include <cstdarg>
#include <vector>


/// TODO: Doxygen
/// TODO: Rethink if everything necessary is included and makes sense
/// 
////////////////////////////////////////////////////////////
/// ctor
////////////////////////////////////////////////////////////
LowLevelSystem::LowLevelSystem() : mCurrentIndex(0), mNumberOfElements(0)
{
  ELOG("LowLevelSystem::ctor");
}

////////////////////////////////////////////////////////////
/// next
////////////////////////////////////////////////////////////
Element* LowLevelSystem::next() 
{
  ELOG("LowLevelSystem::next");
  mCurrentIndex++;
  if(mCurrentIndex >= mNumberOfElements)
    return NULL;
  else
    return mElements[mCurrentIndex];
}

////////////////////////////////////////////////////////////
/// getElement
////////////////////////////////////////////////////////////
int LowLevelSystem::getCntElements()
{
  return mNumberOfElements;
}

////////////////////////////////////////////////////////////
/// getElement
////////////////////////////////////////////////////////////
Element* LowLevelSystem::getElement(int index) 
{
  ELOG("LowLevelSystem::getElement");
  if(index < 0)
    index = mCurrentIndex;
  if(index < mNumberOfElements)
    return mElements[index];
  else
    throw TraceOpenError("LowLevelSystem::getElement", index);
}

////////////////////////////////////////////////////////////
/// next
////////////////////////////////////////////////////////////
void LowLevelSystem::reset() 
{
  ELOG("LowLevelSystem::reset");
  mCurrentIndex = 0;
}

///////////////////////////////////////////////////////////
/// addElement
////////////////////////////////////////////////////////////
void LowLevelSystem::addElement(Element* element) 
{
  ELOG("LowLevelSystem::addElement");

  // 1. copy the core of the element (but not the subelements !)

  Element* e2 = element->copy(false);
  
  // 2. go through the subelements


  mNumberOfElements++;
  mElements.push_back(element);
}

///////////////////////////////////////////////////////////
/// convertTo
/// TODO: Rethink: Does this always work ?
////////////////////////////////////////////////////////////
void LowLevelSystem::convertTo(OpticalSystem* system) 
{
  ELOG("LowLevelSysten::convertTo");

  for(int t=0; t < system->getCntElements(); t++)
    {
      Element* e = system->getElement(t);
      if(e->getCntSubElements() == 0) // no subelements -> add directly
	addElement(e);

      // Now we have to go recursively through all the mSubElements of
      // that element (unfortunately, they might again have subelements !)
      //      LOG("Subelemente = ", e->getCntSubElements());
      for(int u=0; u < e->getCntSubElements(); u++)
	addElement(e->getElement(u));
    }
  

  // TODO: system.mStop noch an SINNVOLLER Stelle reinkopieren
}

///////////////////////////////////////////////////////////
/// show
////////////////////////////////////////////////////////////
void LowLevelSystem::show()
{
  LOG("----------- SHOWING LOWLEVEL ------------------");
  reset();
  do
    {
      LOG("Showing ", mCurrentIndex, getElement()->mInternalElementIndex);
      getElement()->show();
    }
  while(next() !=  NULL);
  LOG("----------- END SHOWING LOWLEVEL --------------");

}

