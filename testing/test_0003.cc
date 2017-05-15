//----------------------------------------------------------------------
// Testing of Point and Direction, espcially ctor, copy ctor, assignment
// and access to these systems
// 
// 15.5.17 Tobias Haist
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
#include <random>
#include "../traceopenerror.h"



// Problem: Logging infos werden auch nach cerr ausgegeben -> unschön.

////////////////////////2
//////////////////////////////////////////////

TraceOpenTest test("Basic Test Point class", "testresults/test_0003_example.log");
#define N 1000

Point gPoints[N];
std::vector<Point*> gPoints2;
Direction gDirections[N];
std::vector<Direction*> gDirections2;

int main(int argc, char* agrv[])
{
  try
    {
      test.newTest("Generation and reading of Points");
      Point p1(1,2,3);
      Point p2(4,5,6);

      real x2 = p2.x().get();
      real x2b = p2.x_const().get();
      real x2c = p2.xValue();

      test.assert(1, fabs(x2-x2b) < 0.00001);
      test.assert(2, fabs(x2-x2c) < 0.00001);

      real y2 = p2.y().get();
      real y2b = p2.y_const().get();
      real y2c = p2.yValue();

      test.assert(3, fabs(y2-y2b) < 0.00001);
      test.assert(4, fabs(y2-y2c) < 0.00001);

      real z2 = p2.z().get();
      real z2b = p2.z_const().get();
      real z2c = p2.zValue();
      test.assert(5, fabs(z2-z2b) < 0.00001);
      test.assert(6, fabs(z2-z2c) < 0.00001);

      test.newTest("Generation of Points in Vectors (as pointers) and Array");
      std::default_random_engine generator;
      std::uniform_real_distribution<real> distribution(-1e20,1e-20);
	
      for(int t=0; t < N; t++)
	{
	  real zufall = distribution(generator);  
	  gPoints[t].x().set(zufall);
	  gPoints[t].y().set(distribution(generator));  
	  gPoints[t].z().set(distribution(generator));  

	  gPoints2.push_back(new Point(gPoints[t].xValue(), gPoints[t].yValue(),
				       gPoints[t].zValue()));
	}

      for(int t=0; t < N; t++)
	{
	  test.assert(7+t*3,
		      fabs(gPoints[t].xValue() - gPoints2[t]->xValue()) < 0.00001);
	  test.assert(8+t*3,
		      fabs(gPoints[t].yValue() - gPoints2[t]->yValue()) < 0.00001);
	  test.assert(9+t*3,
		      fabs(gPoints[t].zValue() - gPoints2[t]->zValue()) < 0.00001);
	}


      test.newTest("Checking Assignment Operation");
      for(int t=0; t < N/2; t++)
	{
	  // check assignment by swapping by Hand
	  Point a = gPoints[t];
	  gPoints[t] = gPoints[N-t-1];
	  gPoints[N-t-1] = a;
	}
      for(int t=0; t < N; t++)
	{
	  test.assert(3007+t*3,
		      fabs(gPoints[t].xValue() - gPoints2[N-t-1]->xValue()) < 0.00001);
	  test.assert(3008+t*3,
		      fabs(gPoints[t].yValue() - gPoints2[N-t-1]->yValue()) < 0.00001);
	  test.assert(3009+t*3,
		      fabs(gPoints[t].zValue() - gPoints2[N-t-1]->zValue()) < 0.00001);
	  //	  std::cerr << gPoints[t].zValue() << std::endl;
	}

      test.newTest("Checking Copy ctor");
      Point* pp = new Point(gPoints[10]);
      test.assert(6009, fabs(pp->yValue() - gPoints[10].yValue() < 0.000001));

      // --------------- NOW THE SAME FOR DIRECTIONS ---------------------------








      test.newTest("Generation and reading of Points");
      Direction d1(1,2,3);
      Direction d2(4,5,6);

      real _x2 = d2.dirCosX().get();
      real _x2b = d2.dirCosX_const().get();
      real _x2c = d2.dirCosXValue();
      test.assert(1, fabs(_x2-_x2b) < 0.00001);
      test.assert(2, fabs(_x2-_x2c) < 0.00001);

      real _y2 = d2.dirCosY().get();
      real _y2b = d2.dirCosY_const().get();
      real _y2c = d2.dirCosYValue();
      test.assert(1, fabs(_y2-_y2b) < 0.00001);
      test.assert(2, fabs(_y2-_y2c) < 0.00001);

      real _z2 = d2.dirCosZ().get();
      real _z2b = d2.dirCosZ_const().get();
      real _z2c = d2.dirCosZValue();
      test.assert(1, fabs(_z2-_z2b) < 0.00001);
      test.assert(2, fabs(_z2-_z2c) < 0.00001);

      test.newTest("Generation of Directions in Vectors (as pointers) and Array");
	
      for(int t=0; t < N; t++)
	{
	  real zufall = distribution(generator);  
	  gDirections[t].dirCosX().set(zufall);
	  gDirections[t].dirCosY().set(distribution(generator));  
	  gDirections[t].dirCosZ().set(distribution(generator));  
	  gDirections2.push_back(new Direction(gDirections[t].dirCosXValue(),
					   gDirections[t].dirCosYValue(),
					   gDirections[t].dirCosZValue()));
	}

      for(int t=0; t < N; t++)
	{
	  test.assert(7+t*3,
		      fabs(gDirections[t].dirCosXValue() - gDirections2[t]->dirCosXValue()) < 0.00001);
	  test.assert(8+t*3,
		      fabs(gDirections[t].dirCosYValue() - gDirections2[t]->dirCosYValue()) < 0.00001);
	  test.assert(9+t*3,
		      fabs(gDirections[t].dirCosZValue() - gDirections2[t]->dirCosZValue()) < 0.00001);
	}


      test.newTest("Checking Assignment Operation");
      for(int t=0; t < N/2; t++)
	{
	  // check assignment by swapping by Hand
	  Direction a = gDirections[t];
	  gDirections[t] = gDirections[N-t-1];
	  gDirections[N-t-1] = a;
	}
      for(int t=0; t < N; t++)
	{
	  test.assert(3007+t*3,
		      fabs(gDirections[t].dirCosXValue() - gDirections2[N-t-1]->dirCosXValue()) < 0.00001);
	  test.assert(3008+t*3,
		      fabs(gDirections[t].dirCosYValue() - gDirections2[N-t-1]->dirCosYValue()) < 0.00001);
	  test.assert(3009+t*3,
		      fabs(gDirections[t].dirCosZValue() - gDirections2[N-t-1]->dirCosZValue()) < 0.00001);

	}

      
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
