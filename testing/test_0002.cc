//----------------------------------------------------------------------
// Testing of very basic optical system generation with spherical surfaces
// and access to these systems
// 
// 11.4.17 Tobias Haist
// ------------------------------------------------------------------------
#include "../elementwithsurfaces.h"
#include "../parameter.h"
#include "../basicdefinitions.h"
#include "../surfacespherical.h"
#include "../opticalsystem.h"
#include "../tracing.h"
#include "../ray.h"
#include "../wave.h"
#include "../logging.h"
#include "../traceopenerror.h"
#include "../materialideal.h"
#include "totest.h"


#include <iostream>
#include "../traceopenerror.h"

using namespace std;

// Problem: Logging infos werden auch nach cerr ausgegeben -> unschön.

////////////////////////2
//////////////////////////////////////////////

TraceOpenTest test("Basic Lens creation test", "testresults/test_0002_example.log");
#define N 100
int main(int argc, char* agrv[])
{
  try
    {
      test.newTest("Generation of 100 lenses");

      Environment env(300, 1);
      vector<ElementWithSurfaces> lenses(N);
      for(int t=0; t < N; t++)
	{
	  // Of course, the numbers do not make any sense
	  lenses[t].standardLens(t*10, t*20, t*30,
		  new MaterialIdeal("Testmat1", &env, t*40, t*50), -t*60);
	}

      
      test.newTest("Generation of 100 lenses: Finished, Now Testing");
      // .... Here we test if they are OK.
      for(int t=0; t < N; t++)
	{
	  SurfaceSpherical* surface = dynamic_cast<SurfaceSpherical*>
	    (lenses[t].getSurface(0));
	  double a = surface->getRadiusPointer()->get();
	  test.assert(1, fabs(a-t*10) < 0.00001);

	  surface = dynamic_cast<SurfaceSpherical*>
	    (lenses[t].getSurface(1));
	  a = surface->getRadiusPointer()->get();
	  test.assert(2, fabs(a-t*20) < 0.00001);

	  double z = surface->getPosition()->getZ().get();
	  test.assert(3, fabs(z-t*30) < 0.00001);

	  double diameter = surface->getDiameter()->get();
	  test.assert(3, fabs(diameter-t*60) < 0.00001);

	  Material* mat = lenses[t].getMaterial(0);
	  test.assert(4, mat->getName() == "Testmat1");
	}

      // Now, we do the same but try out some simpler accessing methods
      for(int t=0; t < N; t++)
	{
	  SurfaceSpherical* surface = dynamic_cast<SurfaceSpherical*>
	    (lenses[t].getSurface(0));
	  double a = surface->getRadius();
	  test.assert(1, fabs(a-t*10) < 0.00001);

	  surface = dynamic_cast<SurfaceSpherical*>
	    (lenses[t].getSurface(1));
	  a = surface->getRadius();
	  test.assert(2, fabs(a-t*20) < 0.00001);

	  double z = lenses[t].getZPosition(1);
	  test.assert(3, fabs(z-t*30) < 0.00001);

	  Material* mat = lenses[t].getMaterial(0);
	  test.assert(4, mat->getName() == "Testmat1");
	}
      // TODO: We should also test the MaterialIdeal parameters

      //       throw TraceOpenError("TestException", 4);

    }

  // ---------------------------------------------------------------------------
 catch(TraceOpenError& e)
   {
     std::cout << "Exception "<< " ErrNo = " << e.mErrno << std::endl;
     test.mCntErrors++;
   }
 catch(std::exception& e)
   {
     std::cout << "StdLib Exception: " << e.what() << std::endl;
     test.mCntErrors++;
   }

 catch(...)
   {
     test.mCntErrors++;
     std::cout << "TraceOpen: We had an unknown exception" << std::endl;
   }
  ////////////////////////////////////////////////////////////


  test.finalMessage();
}
