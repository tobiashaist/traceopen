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
#include "tracing.h"
#include "ray.h"
#include "wave.h"
#include "logging.h"
#include "traceopenerror.h"
#include "materialideal.h"


#include <iostream>


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
    Ray l1;
    Point p1(3,3,3);
    Direction d1(3,3,3);

    Ray l1b(633e-9, 1, &p1, &d1);
    Wave l2;
  
    if(argc == 1)
      light = &l1;   // Ray
    else
      light = &l2;   // Scalar Wave
    
    tracing.init(light);

    // --------------- Check copy und assignemnt OP
    Parameter<real> a(3.2);
    a.setMaximum(7);
    Parameter<real> b(a);
    a.setMaximum(8);
    std::cout << b.getValue() << "  " << b.getMaximum() << std::endl;
    Parameter<real> c;
    c = a;
    std::cout << c.getValue() << "  " << c.getMaximum() << std::endl;
    // -----------------------------------------------------------
    
  // Ab jetzt kann man im Prinzip "tracing" benutzen.
  // Allerdings braucht man nun noch ein optisches System.
  //
  // Ganz simpel: Mal zwei sphärische Oberflächen
  ////////////////////////////////////////////////////////////
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

#else
  ElementWithSurfaces e1,e2;

  // r1, r2, thickness, Material, diameter
  e1.standardLens(10e-3, -10e-3, 3e-3,
		  new MaterialIdeal("Testmat1", &env, 1.57,50),10e-3);
  e2.achromat(10e-3, -10e-3, 20e-33, 2e-3, 1e-3,
	      new MaterialIdeal("Testmat1", &env,1.57,50),
	      new MaterialIdeal("Testmat2", &env,1.47,20), 10e-3);

  OpticalSystem sys;
  sys.addElement(&e1);
  sys.addElement(&e2);

#endif

  // ----- Und nun können wir da mal durchtracen ------------------

  tracing.trace(light, &sys);
  std::cout << "Finished without crash" << std::endl;
  }






 
 catch(TraceOpenError& e)
   {
     std::cout << "Exception "<< e.what() << " ErrNo = " << e.errno << std::endl;
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
