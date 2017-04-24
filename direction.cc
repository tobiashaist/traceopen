////////////////////////////////////////////////////////////
/// \file point.cc
/// \brief class Point
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "direction.h"

//////////////////////////////////////////////////////////////////////
/// \param a global direction cosine with respect to x axis
/// \param b global direction cosine with respect to y axis
/// \param c global direction cosine with respect to z axis
//////////////////////////////////////////////////////////////////////
Direction::Direction(const real a, const real b, const real c) : mDirCosX(a), mDirCosY(b), mDirCosZ(c)
{
  ;
}

// TODO: Checken, ob die automatisch generierten
// copy constructors und assignment operators
// sinnvoll und korrekt arbeiten
//
#if 0
Direction::Direction(Direction& dir)  
{
  
}
#endif
