////////////////////////////////////////////////////////////
/// \file totest.h
/// \brief include file for class TraceOpenTest
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef TOTEST_HPP 
#define TOTEST_HPP

#include <string>

////////////////////////////////////////////////////////////
///  \brief TraceOpenTest is a simple small class that is used within our test programs
///   to have the test output always in the same layout
////////////////////////////////////////////////////////////
class TraceOpenTest
{
  
public:

  TraceOpenTest(std::string name, std::string filenname);  ///< ctor
  void finalMessage();		         ///< finally we output if everything passed OK
  void writeTime();			 ///< put the time stamp out to file
  void assert(int nr, bool isCorrect);   ///< The main test thing
  void newTest(std::string testname);    ///< start a new test
  
  int mCntErrors;		        ///< How many errors have been found
 protected:
  std::string mName;			///< name of Test
  std::string mFilename;		///< Filename where we want to save the results
  int mCntTests;                        ///< How many tests have been performed
  int mCntAssertions;	           	///< How many assertions have been tested 
};

#endif
