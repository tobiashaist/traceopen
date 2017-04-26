//----------------------------------------------------------------------
// Einfaches kleines Progrämmchen, das die Testfascilities demonstriert,//
//
// 11.4.17 Tobias Haist
// ------------------------------------------------------------------------
#include "../elementwithsurfaces.h"
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


// Problem: Logging infos werden auch nach cerr ausgegeben -> unschön.

//////////////////////////////////////////////////////////////////////

TraceOpenTest test("Example for a Test", "testresults/test_0001_example.log");

int main(int argc, char* agrv[])
{


  try
    {
      test.newTest("Generation of many Rays");
      // .... Here we test something
      test.assert(1, 3 == 3);
      test.assert(2, 3 == 3);
      throw TraceOpenError("TestException", 4);
      
      test.newTest("Generation of many Rays Part 2");
      test.assert(1, 3 == 3);
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
