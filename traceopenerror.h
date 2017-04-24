////////////////////////////////////////////////////////////
/// \file traceopenerror.h
/// \brief include file for Exceptions
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 1999
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef TRACEOPENERROR_HPP 
#define TRACEOPENERROR_HPP

#include <string>

class TraceOpenError : public std::runtime_error 
{
 public:

 TraceOpenError(std::string const& s, int nr =  0) : std::runtime_error("TraceOpen" + std::string(":") + s), errno(nr)
    {
    }

 public:
  int errno;

};

#endif
