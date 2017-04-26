////////////////////////////////////////////////////////////
/// \file ray.cc
/// \brief class Ray
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "ray.h"
#include "logging.h"

//////////////////////////////////////////////////////////////////////
/// \param lambda wavelength (in m)
/// \param intensity intesity in W/m^2
//////////////////////////////////////////////////////////////////////
Ray::Ray(const real lambda, const real intensity) :
  Light(typeLightRay, lambda, intensity)
{
  LOG("Ray ctor A");
}

//////////////////////////////////////////////////////////////////////
/// \param lambda wavelength (in m)
/// \param intensity intesity in W/m^2
/// \param p start point of the ray (pointer due to efficiency)
/// \param dir start direction of the ray (pointer due to efficiency)
//////////////////////////////////////////////////////////////////////
Ray::Ray(const real lambda, const real intensity, Point* const p, Direction* const dir) :
  Light(typeLightRay, lambda, intensity), mPoint(*p), mDirection(*dir)
{
  LOG("Ray ctor B");

}


//////////////////////////////////////////////////////////////////////
/// \return Point of the origin (arbitrary coordinates)
//////////////////////////////////////////////////////////////////////
Point& Ray::getPoint() 
{
  return mPoint;
}


//////////////////////////////////////////////////////////////////////
/// \return x coordinate (global coordinates !) of Ray
//////////////////////////////////////////////////////////////////////
// Problem: Kann die Funktion nicht als const definieren
// weil da eben die Funktion mPoint.X() eine Referenz (und zwar
// keine Referenz auf ein const Objekt zurückgibt.....
//
// Das folgende funkt nicht, weil die Funktion ja verspricht, dass sie
// Ray garantiert nicht ändert. Dann ruft sie aber eine Funktion auf,
// nämlich X(), die NICHT verspricht, ray nicht zu ändern.
// Es könnte ja sein, dass X() ändert und dann wäre die Behauptung
// dass getX Ray nicht ändert falsch -> Compile Fehler !
// real Ray::getX() const
// {
//   Parameter<real> const a =  (mPoint.X());
// }
//
// An dieser Stelle rächt sich jetzt bereits, dass wir eben (letztlich aus
// Effizienzgründen) die Funktion X() eingeführt haben, die eine Referenz
// zurückgibt und deshalb nicht const sein kann!!!
//
// Also: ist die Lösung, dass eine zweite getter Funktion in Point
// definiert wird. Das ist etwas unelegant, aber mir fällt da keine
// besser const correct Lösung ein.
real Ray::getX() const
{
  return mPoint.getX().get();
}

////////////////////////////////////////////////////////////
/// \return global y coordinate of ray
////////////////////////////////////////////////////////////
real Ray::getY() const
{
  return mPoint.getY().get();
}

////////////////////////////////////////////////////////////
/// \return global z coordinate of ray
////////////////////////////////////////////////////////////
real Ray::getZ() const
{
  return mPoint.getZ().get();
}


////////////////////////////////////////////////////////////
/// \param set the global x coordinate of ray
////////////////////////////////////////////////////////////
void Ray::setX(const real x) 
{
  mPoint.X().set(x);
}


////////////////////////////////////////////////////////////
/// \param set the global y coordinate of ray
////////////////////////////////////////////////////////////
void Ray::setY(const real y) 
{
  mPoint.Y().set(y);
}

////////////////////////////////////////////////////////////
/// \param set the global x coordinate of ray
////////////////////////////////////////////////////////////
void Ray::setZ(const real z) 
{
  mPoint.Z().set(z);
}


////////////////////////////////////////////////////////////
/// \param set the global x,y,z coordinate of ray, global coord.
////////////////////////////////////////////////////////////
void Ray::setXYZ(const real x, const real y, const real z )
{
  mPoint.X().set(x);
  mPoint.Y().set(y);
  mPoint.Z().set(z);
}




////////////////////////////////////////////////////////////
/// \param set the global direction cosines to the axes, global coord.
////////////////////////////////////////////////////////////
void Ray::setDirCosXYZ(const real x, const real y, const real z )
{
  mDirection.dirCosX().set(x);
  mDirection.dirCosY().set(y);
  mDirection.dirCosZ().set(z);
}



////////////////////////////////////////////////////////////
/// \return the direction cosine to the x axis, global coordinates
////////////////////////////////////////////////////////////
real Ray::getDirCosX() const
{
  return mDirection.getDirCosX().get();
}

////////////////////////////////////////////////////////////
/// \return the direction cosine to the z axis, global coordinates
////////////////////////////////////////////////////////////
real Ray::getDirCosZ() const
{
  return mDirection.getDirCosZ().get();
}

////////////////////////////////////////////////////////////
/// \return the direction cosine to the y axis, global coordinates
////////////////////////////////////////////////////////////
real Ray::getDirCosY() const
{
  return mDirection.getDirCosY().get();
}


////////////////////////////////////////////////////////////
/// \param set the global direction cosine to the  x-axis
////////////////////////////////////////////////////////////
void Ray::setDirCosX(const real x) 
{
  mDirection.dirCosX().set(x);
}


////////////////////////////////////////////////////////////
/// \param set the global direction cosine to the y-axis
////////////////////////////////////////////////////////////
void Ray::setDirCosY(const real y) 
{
  mDirection.dirCosY().set(y);
}

////////////////////////////////////////////////////////////
/// \param set the global direction cosine to the  z-axis
////////////////////////////////////////////////////////////
void Ray::setDirCosZ(const real z) 
{
  mDirection.dirCosZ().set(z);
}

