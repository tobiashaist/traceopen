//----------------------------------------------------------------------
// Einfaches kleines Progrämmchen, das demonstriert, dass das Grunddesign
// in der Lage ist, sinnvoll zwischen verschiedenen Lichtmodellen
// umzuschalten.
//
// -- Ohne Argument wird ein Ray durchgetraced
// .. mit Argument (also ./test 1) wird eine Wave durchgetraced

// 11.4.17 Tobias Haist
// ------------------------------------------------------------------------
#include "elementwithsurfaces.h"
#include "surfacespherical.h"
#include "opticalsystem.h"
#include "ray.h"
#include "tracing.h"
#include "wave.h"
#include "logging.h"
#include "computedpickup.h"
#include "traceopenerror.h"
#include "materialideal.h"
#include "raybundle.h"


#include <iostream>
#include <vector>


//////////////////////////////////////////////////////////////////////


Tracing tracing;

int main(int argc, char* agrv[])
{
#if LOGFILE
   freopen( "traceopen.log", "w", stderr );
#endif
  
  // ----------------------------------------------------------
try
  {

    Environment env(300, 1);
    Light *light;
    //    Point p1(3,3,3);
    //    Point p2(6,3,3);
    
    //    p2.X().set(7);
    //    std::cout << p2.X().get() << std::endl;
    Direction d1(3,3,3);

    //    Ray l1b(633e-9, 1, &p1, &d1);
    //    l1b.getDirCosX();
    
    //    Point ax = l1b.getPoint();
    //  std::cout << "Nun =  " << ax.X().get() << std::endl;


    Ray l1;    
    Wave l2;

    if(argc == 1)
      light = &l1;   // Ray
    else
      light = &l2;   // Scalar Wave

    LOG("A");
    OpticalSystem sys;
    
    LOG("B");


    
    // We do not come out here !
    LOG("C");

#if 0    
    // --------------- Check copy und assignemnt OP
    Parameter<real> a(3.2);
    a.setMaximum(7);
    Parameter<real> b(a);
    a.setMaximum(8);
    std::cout << b.get() << "  " << b.getMaximum() << std::endl;
    Parameter<real> c;
    c = a;
    std::cout << c.get() << "  " << c.getMaximum() << std::endl;
    // -----------------------------------------------------------
    
  // Ab jetzt kann man im Prinzip "tracing" benutzen.
  // Allerdings braucht man nun noch ein optisches System.
  //
  // Ganz simpel: Mal zwei sphärische Oberflächen
  ////////////////////////////////////////////////////////////
#endif
    
#if 0
  SurfaceSpherical s(3.2, 10e-3, Point(3,2,1));
  SurfaceSpherical s2(2.1,10e-3, Point(3,2,1));
  Material m(1.57, 50);
  ElementWithSurfaces e;
  e.addSurface(&s, &m);
  e.addSurface(&s2, &m);

  OpticalSystem sys;
  sys.addElement(&e);
  sys.addElement(&e);

#endif

#if 1 
  ElementWithSurfaces e1,e2;

  // r1, r2, thickness, Material, diameter
  e1.standardLens(10e-3, -10e-3, 3e-3,
		  new MaterialIdeal("Testmat1", &env, 1.57,50),10e-3);
  e2.achromat(10e-3, -10e-3, 20e-33, 2e-3, 1e-3,
	      new MaterialIdeal("Testmat1", &env,1.57,50),
	      new MaterialIdeal("Testmat2", &env,1.47,20), 10e-3);

  //
  
  //  ElementWithSurfaces* ep = dynamic_cast<ElementWithSurfaces*> (sys.addElement(&e1));

  LOG("D");
  sys.addElement(&e1);
  int indexlinse2 = sys.addElement(&e2);

  // ----- Und nun können wir da mal durchtracen ------------------
  tracing.init(light, &sys );
  LOG("E");
  tracing.trace();
  LOG("F");
  // ----- We come to a typical solve ----------------------

  // Here we run now in a real problem!
  // We get back something which IN GENERAL does not
  // have a surface !
  // Therefore how should that in general work ?! It cannot!
  // So the typical solution would be to cast:
  
  Element* e = sys.getElement(1);
  LOG("G");
  Surface* s = static_cast<ElementWithSurfaces*>(e)->getSurface(0);
  // This brings in a certain risk and the programmer definitely has to
  // know what he is doing ! Not perfect.

  // But how should we know otherwise get the Parameter?
  // One option would be to get the Parameter right when creating ....

  SurfaceSpherical sx1(3.2, 10e-3, Point(3,2,1));
  SurfaceSpherical sx2(2.1,10e-3, Point(3,2,1));
  MaterialIdeal m("test", &env, 1.57, 50);
  ElementWithSurfaces ex;
  LOG("H");
  ex.addSurface(&sx1, new   MaterialIdeal("test", &env, 1.57, 50));
  ex.addSurface(&sx2, &m);

  // so now, I can of course directly use ex or even sx1 and do not have to cast:
  // So that would be normally preferred ... and otherwise we would
  // have to cast ....


  Parameter<real>* para  = sx1.getRadiusPointer();
  Parameter<real>* para2  = sx2.getRadiusPointer();
  LOG("I");
  ComputedPickup pickup1(&tracing, typePickupLinear, para, para2, -3, 2 );
#endif
  std::cout << "Finished without crash" << std::endl;
  RayBundle();
  }

 
 catch(TraceOpenError& e)
   {
     //     std::cout << "Exception "<< e.what() << " ErrNo = " << e.errno << std::endl;
     std::cout << "Exception "<<  " ErrNo = " << e.mErrno << std::endl;
   }
 catch(std::exception& e)
   {
     std::cout << "StdLib Exception: " << e.what() << std::endl;
   }

 catch(...)
   {
     std::cout << "TraceOpen: We had an unknown exception" << std::endl;
   }
  ////////////////////////////////////////////////////////////
}
