////////////////////////////////////////////////////////////
/// \file jonesmatrix.h
/// \brief include file for class JonesMatrix
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef JONESMATRIX_HPP 
#define JONESMATRIX_HPP

#include "basicdefinitions.h"
#include "parameter.h"



////////////////////////////////////////////////////////////
///  \brief JonesMatrix is just the Jones matrix of an element  
////////////////////////////////////////////////////////////
///  
///  In TraceOpen polarized light is represented using Jones matrices
///  
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
// TODO: Everrything !
////////////////////////////////////////////////////////////
class JonesMatrix
{
public:
  JonesMatrix(real ra, real ia, real rb, real ib, real rc, real ic, real rd, real id);
  
protected:
  Parameter<real> mRXX;		///< real part Element a (xx)
  Parameter<real> mIXX;		///< imag part Element a (xx)
  Parameter<real> mRXY;		///< real part Element b (xy)
  Parameter<real> mIXY;		///< imag part Element b (xy)
  Parameter<real> mRYX;		///< real part Element a (yx)
  Parameter<real> mIYX;		///< imag part Element a (yx)
  Parameter<real> mRYY;		///< real part Element a (yy)
  Parameter<real> mIYY;		///< imag part Element a (yy)

};

#endif
