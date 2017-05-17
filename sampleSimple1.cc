//----------------------------------------------------------------------
// Einfaches kleines Progrämmchen, das demonstriert, dass das Grunddesign
// in der Lage ist, sinnvoll zwischen verschiedenen Lichtmodellen
// umzuschalten.
//
// -- Ohne Argument wird ein Ray durchgetraced
// .. mit Argument (also ./test 1) wird eine Wave durchgetraced

// 11.4.17 Tobias Haist
// ------------------------------------------------------------------------
#include "tracing.h"
#include "elementwithsurfaces.h"
#include "surfacespherical.h"
#include "opticalsystem.h"
#include "ray.h"
#include "wave.h"
#include "logging.h"
#include "computedpickup.h"
#include "traceopenerror.h"
#include "materialideal.h"
#include "raybundle.h"
#include "interaction.h"


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
    Ray l1;    
    Wave l2;

    if(argc == 1)
      light = &l1;   // Ray
    else
      light = &l2;   // Scalar Wave

    OpticalSystem sys;
#if 0
    ElementWithSurfaces e1,e2;
    e1.standardLens(10e-3, -10e-3, 3e-3,
		    new MaterialIdeal("Testmat1", &env, 1.57,50),10e-3);
    e2.achromat(10e-3, -10e-3, 20e-33, 2e-3, 1e-3,
		new MaterialIdeal("Testmat1", &env,1.57,50),
		new MaterialIdeal("Testmat2", &env,1.47,20), 10e-3);
    sys.addElement(&e1);
    sys.addElement(&e2);
#endif

#if 0    
    // r, n, thickness
    sys.patentInput(3,INFINITY, AIR, 100e-3,
		   50e-3, 1.5, 5e-3,
		   -50e-3, AIR, 100e-3
		   );
#else
    LOG("vor paraxial system");
    sys.paraxialSystem(3, 100e-3, 100e-3,
		       10e-3, 100e-3,
		       15e-3, 1000e-3
		       );
    LOG("nach paraxial system");
#endif

    
    //    sys.show();

    // ----- Und nun können wir da mal durchtracen ------------------
    tracing.init(light, &sys );
    tracing.trace();

  std::cout << "Finished without crash" << std::endl;
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
