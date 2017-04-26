////////////////////////////////////////////////////////////
/// \file point.h
/// \brief include file for class Point
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef POINT_HPP 
#define POINT_HPP

#include "basicdefinitions.h"
#include "parameter.h"

#include <iostream>

////////////////////////////////////////////////////////////
///  \brief Point manages Points/Positions in Space
////////////////////////////////////////////////////////////
///  
///  This is the basic class for representing the position of a point.
///  The point can be given, of course, in different coordinate systems.
///  However, it is stored in "the" one and only global coordinate system.
///  Methods for obtaining the position in other systems are given.
///
/// Beachte: Wir werden nicht in Versuchung geraten, das per Referenzen auf die einzelen
/// Werte zu lösen weil
/// wir damit die Kapselung kaputt machen und dann z.B. nicht mehr Min und Max geprüft  
/// wird !
/// Daher brauchen wir für die häufigen Sachen eben setter UND getter !
/// z.B. Parameter<real>& getY(void) {return mY;} 
///
/// Man könnte natürlich auch jeweils nen Parameter<real> statt eine Referenz
/// auf selbigen rückgeben. 
/// Aber das wäre zu ineffizient !
/// Daher müssen wir mit Referenzen hier arbeiten und daher können wir hier auch
/// nicht von const ausgehen und da kommt ein gewisses Risiko rein .....
/// Das muss aber sein !
/// 
/// Nomenclature: Since we return a reference we call the function not getX but X
/// to set a variable 
///
/// But now it gets even more complicated due to the const correctness that we
/// want to use for the library.
/// E.g. the Function Ray::getX() should be const and it would call Point::X()
/// to finally get something. But this will not work because X() cannot be const.
/// Therefore we would need A SECOND getX() function which will really deliver just
/// a const x and just for reading. This is why it is called getX().
///
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class Point {

public:
  Point(real x=0, real y=0, real z=0);    ///< construction with global coordinates
  Parameter<real>& X(void) {return mX;}  ///< get reference onto point x global coordinate
  Parameter<real>& Y(void) {return mY;}  ///< get reference onto point y global coordinate
  Parameter<real>& Z(void) {return mZ;}  ///< get reference onto point z global coordinate

  const Parameter<real>& getX(void) const {return mX;} ///< get reference onto point x global coordinate
  const Parameter<real>& getY(void) const {return mY;} ///< get reference onto point x global coordinate
  const Parameter<real>& getZ(void) const {return mZ;} ///< get reference onto point x global coordinate
  
 protected:
  Parameter<real> mX;			///< x coordinate in global coordinate system
  Parameter<real> mY;			///< y coordinate in global coordinate system
  Parameter<real> mZ;			///< z coordinate in global coordinate system 
};

#endif
