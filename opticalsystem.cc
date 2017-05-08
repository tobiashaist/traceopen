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
#include "logging.h"

////////////////////////////////////////////////////////////
/// \param e Pointer to Element to be added to end of list
/// \return number of surfaces
////////////////////////////////////////////////////////////
// TODO: Here we might run into typical pointer problems.
// e.g. the main program which calls addElement might
// delete the original object. That, of course would lead to
// desaster.
// Or: The main program might send the same object to optical
// systems or add them twice .... then the user changes later a
// parameter of one of the surfaces and then (unexpected & unwanted) the
// other surface will change too .... lots of such strange things
// might happen in case that one somehow does something wrong.
// So.... our options are:
// 1) Perform at this position a deep copy of the element (costly)
// 2) Use unique_ptr  (at the cost of making the code more ugly/complicated)
// 3) Use call by value (costly)
// 4) Do nothing and Hope that the thing is used correct
//
// The same problem is at
// - lightbundle
// - elementwithsurfaces
// - database
//
// I guess the deep copy approach is best suited here because is a minor
// problem (it will not be called (often) during optimization.
// we still, however, need pointers because of polymorphism.
// But: at the end: The optical system will be held responsible for
// the Elements.
// getElement will then return a pointer to the element
// but the main program is NOT allowed to somehow delete the pointed object.
// Again: unique_pointer might be used but that might again lead
// to ugly casts (actually, I guess not !).
//
// So finally ... the design decision is to replace ethe Element*
// here with unique Pointers with clear ownership 
//
// Even better: we can forget the deep copy during addElement
// by transfering ownership by the move() function
// and if we use vector, I guess , it will be even automatically transferred.
// Therefore: No problem.
//
// But: then the caller code cannot use the Element anymore.
// However: addElement might return an Element* which
// can be casted to the special element and which then
// can be changed (e.g. Parameter set)
// 
// Might lead to lots of casts ....
// It might be also a (better ?) option to return then really the unique_ptr
// 
int OpticalSystem::addElement(Element * const  e)
{
  ELOG("addElement");
  Element* ec = e->copy();   // for lens this points to a newly created Lens !
  mElements.push_back(move(e->mSmartPtrElement));  
  std::cerr << "Number of Elements in mElements = " << mElements.size() << std::endl;
  return mElements.size();
}

////////////////////////////////////////////////////////////
/// ctor
////////////////////////////////////////////////////////////
OpticalSystem::OpticalSystem() 
{
    ELOG("ctor OpticalSystem");
}

////////////////////////////////////////////////////////////
/// \param nr index (0 ... size) of element of the optical system
/// \return  Pointer to Element number nr
////////////////////////////////////////////////////////////
Element* const OpticalSystem::getElement(const int nr) const
{
  ELOG("getElement");
  std::cerr << "Number of Elements in mElements = " << mElements.size() << std::endl;
  return mElements[nr].get();
}

////////////////////////////////////////////////////////////
/// \param nr index (0 ... size) of element of the optical system
/// \param  Pointer to Element number nr
/// \return -1 if index is out of bounds, otherwise: nr
////////////////////////////////////////////////////////////
int OpticalSystem::setElement(Element* const e, const int nr)
{
  ELOG("setElement");
  if(nr > mElements.size())
    return -1;

  *mElements[nr] = *e;
  // TODO: This has to be changed/checked !
  return nr;
}

////////////////////////////////////////////////////////////
/// Just for debugging purposes
////////////////////////////////////////////////////////////
void OpticalSystem::show()
{
  ELOG("SHOW OPTICALSYSTEM", static_cast<int>(mElements.size()));
  for(int t=0; t < mElements.size(); ++t)
    mElements[t]->show();
  ELOG("END OF SHOW OPTICALSYSTEM");
}
