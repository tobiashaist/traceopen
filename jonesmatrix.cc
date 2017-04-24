////////////////////////////////////////////////////////////
/// \file jonesmatrix.cc
/// \brief class JonesMatrix
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "jonesmatrix.h"

////////////////////////////////////////////////////////////
/// \param e Pointer to Element to be added to end of list
////////////////////////////////////////////////////////////
JonesMatrix::JonesMatrix(real ra, real ia, real rb, real ib, real rc,
			 real ic, real rd, real id) : mRXX(ra), mIXX(ia),
						      mRXY(rb), mIXY(ib),
						      mRYX(rc), mIYX(ic),
						      mRYY(rd), mIYY(id) 
{
  ;
}
