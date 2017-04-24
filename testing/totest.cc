////////////////////////////////////////////////////////////
/// \file totest.cc
/// \brief class TraceOpenTest 
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include <iostream>
#include <cstdio>
#include "totest.h"

using namespace std;

////////////////////////////////////////////////////////////
/// \param name Name of the test
/// \param filename filename where the results should be stored
////////////////////////////////////////////////////////////
TraceOpenTest::TraceOpenTest(std::string name, std::string filename) :
  mName(name), mFilename(filename), mCntErrors(0), mCntTests(0),
  mCntAssertions(0)
{
  freopen( mFilename.c_str(), "w", stdout);
  cout << "---------------------------------------------------------------" << endl;
  writeTime();
  cout << mName << ": " << endl;
}


////////////////////////////////////////////////////////////
void TraceOpenTest::finalMessage()
{
  writeTime();
  cout << mCntAssertions << " Assertions checked " << endl;
  if(mCntErrors == 0)
    cout << "All tests passed" << endl;
  else
    cout << "Test failed " << mCntErrors << " errors found "<< endl;
}

////////////////////////////////////////////////////////////
void TraceOpenTest::writeTime()
{
  std::string time_str;
  time_t raw_time;
  time( & raw_time );
  time_str = ctime( &raw_time );

  std::cout <<    time_str.substr( 0 , time_str.size() - 1 ) << " ";
}
					       

////////////////////////////////////////////////////////////
/// \param isCorrect true -> indeed assertion passed, OK
////////////////////////////////////////////////////////////
void TraceOpenTest::assert(int nr, bool isCorrect)
{
  ++mCntAssertions;
  if(!isCorrect) 
  {                // Test not passed !
    writeTime();
    cout << "Assertion Nr. " << nr << " not passed !" << endl;
    ++mCntErrors;
  }
}

////////////////////////////////////////////////////////////
/// \param isCorrect true -> indeed assertion passed, OK
////////////////////////////////////////////////////////////
void TraceOpenTest::newTest(std::string testname)
{
  writeTime();
  cout << "Test " << mCntTests << " " << testname << endl;
  ++mCntTests;
}
