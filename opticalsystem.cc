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
#include "surfacespherical.h"
#include "materialideal.h"
#include <cstdarg>



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
// OK .. after having implemented things with SmartPointers and getting it
// nearly to work correctly, I decided: It gets to complicated in this case
// nobody will understand it. Just too much ....
// Therefore: We might use another solution in the future.
// Right now, I returned to raw pointers.
// This of course is risky. It boils always down to the question
// "who is or feals responsible to the created objects using new ?")
//
// Currently we do it like that: The class that created (using new) the
// objects (mainly Elements (surfaces etc.)) will be responsible to
// delete.
// TODOe: Das ist noch nicht voll korrekt / durchdacht !

// TODO: Doxygen

int OpticalSystem::addElementWithCopy(Element * const  e)
{
  ELOG("OpticalSysten::addElementWithCopy");
  Element* ec = e->copy();   // for lens this points to a newly created Lens 
  
  mElements.push_back(ec);  
  return mElements.size();
}


int OpticalSystem::addElement(Element * const  e)
{
  ELOG("OpticalSysten::addElement");
  mElements.push_back(e);  
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
  LOG("getElement", nr, mElements.size());
  //  std::cerr << "Number of Elements in mElements = " << mElements.size() << std::endl;
  return mElements[nr];
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
  LOG("SHOW OPTICALSYSTEM", static_cast<int>(mElements.size()));
  for(int t=0; t < mElements.size(); ++t)
    mElements[t]->show();
  LOG("END OF SHOW OPTICALSYSTEM");
}

////////////////////////////////////////////////////////////
int OpticalSystem::getCntElements()
{
  return mElements.size();
}


////////////////////////////////////////////////////////////
// TODO: implement it correctly (and test it)
void OpticalSystem::patentInput(int nsurfaces, ...)
{
 va_list ap;
 va_start(ap, nsurfaces);

 SurfaceSpherical* s; 
 real z = 0;
 Environment dummyenv(300, 1);  // TODO
 
 for(int t = 0; t < nsurfaces; t++)
   {
     real r = va_arg(ap, double);
     real n = va_arg(ap, double);
     real thickness = va_arg(ap, double);

     s = new SurfaceSpherical(r, 10e-3, Point(0,0,z));
     s->show();
  
     z += thickness;
     // TODO: Hier noch Diameter auf Auto setzen
     LOG("OpticalSystem::patentInput within the loop");
     addElement(s); // TODO new MaterialIdeal("AutoMaterial", &dummyenv, n, INFINITY));
   }
 va_end(ap);
 LOG("OpticalSystem::patentinput exit point");
}


////////////////////////////////////////////////////////////
// TODO: implement it correctly (and test it)
void OpticalSystem::paraxialSystem(int nlenses, ...)
{
 va_list ap;
 va_start(ap, nlenses);
 ParaxialLens l;

 real z = 0;
 Environment dummyenv(300, 1);  // TODO
 
 for(int t = 0; t < nlenses; t++)
   {
     real distance = va_arg(ap, double);
     real focallength = va_arg(ap, double);
     LOG("Focallength", focallength);
     LOG("Distanz", distance);
     l.setFocalLength(focallength);
     l.getPosition()->z().set(z);
     addElementWithCopy(&l);
     z += distance;
     // TODO: Hier noch Diameter auf Auto setzen
   }

 va_end(ap);
 LOG("Ende paraxialSystem");
}
