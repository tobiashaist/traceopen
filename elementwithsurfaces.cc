////////////////////////////////////////////////////////////
/// \file elementwithsurfaces.cc
/// \brief class ElementWithSurfaces
///  \date 15.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "elementwithsurfaces.h"
#include "surfacespherical.h"
#include "logging.h"

//////////////////////////////////////////////////////////////////////
ElementWithSurfaces::ElementWithSurfaces() : mCntSurfaces(0), mSurfaces(10), mMaterials(10)
{
  LOG("CTOR Element With Surfaces");
  for(int t=0; t< 10; t++)
    {
      mSurfaces[t] = NULL;
      mMaterials[t] = NULL;
    }
}

//////////////////////////////////////////////////////////////////////
ElementWithSurfaces::ElementWithSurfaces(ElementWithSurfaces& e) 
{
  LOG("COPY CTOR Element With Surfaces");
  mSurfaces= e.mSurfaces;
  mMaterials = e.mMaterials;
  mCntSurfaces = e.mCntSurfaces;
}

//////////////////////////////////////////////////////////////////////
ElementWithSurfaces::~ElementWithSurfaces()
{
  LOG("DTOR Element With Surfaces");
  for(int t=0; t< mSurfaces.size(); t++)
    if(mSurfaces[t] != NULL)
      delete mSurfaces[t];
  for(int t=0; t< mMaterials.size(); t++)
    if(mMaterials[t] != NULL)
      delete mMaterials[t];
}

//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
//////////////////////////////////////////////////////////////////////
ElementWithSurfaces* ElementWithSurfaces::copy()
{
  mSmartPtrElement.reset(new ElementWithSurfaces(*this)); // here we generate
  // a new Element and the mSmartPtrElement gets Ownership for that
    
  return dynamic_cast<ElementWithSurfaces*>(mSmartPtrElement.get());
}

//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
//////////////////////////////////////////////////////////////////////
Surface* ElementWithSurfaces::getSurface(int surfacenumber)
{
  // TODO: error checks
  LOG("ElementWithSurfaces::getSurface",surfacenumber);
  return mSurfaces[surfacenumber];
}

//////////////////////////////////////////////////////////////////////
/// \param s Pointer to surface
/// \param m Pointer to material
//////////////////////////////////////////////////////////////////////
void ElementWithSurfaces::addSurface(Surface* const s,  Material* const m)
{
  LOG("addSurface");
  if(mCntSurfaces < 10)
    {
      mSurfaces.push_back(s);
      mMaterials.push_back(m);
    }
  else
    {
      mSurfaces[mCntSurfaces] = s;
      mMaterials[mCntSurfaces] = m;
    }
  mCntSurfaces++;
}



//////////////////////////////////////////////////////////////////////
/// \param r1 radius of curvature surface 1
/// \param r2 radius of curvature surface 2
/// \param r3 radius of curvature surface 3
/// \param thickness1 thickness between surface 1 and 2
/// \param thickness2 thickness between surface 2 and 3
/// \param m1 Pointer to material 1
/// \param mw Pointer to material 2
/// \param diameter lens diameter
//////////////////////////////////////////////////////////////////////
void ElementWithSurfaces::achromat(const real r1, const real r2, const real r3,
				   const real thickness1,
				   const real thickness2, Material* const m1,
				   Material* const m2,
				   const real diameter)
{
  SurfaceSpherical* s = new SurfaceSpherical(r1, diameter, Point(0,0,0));
  mSurfaces[0] = s;
  mMaterials[0] = m1;

  s = new SurfaceSpherical(r2, diameter, Point(0,0,thickness1));
  mSurfaces[1] = s;
  mMaterials[1]= m2;

  s = new SurfaceSpherical(r3, diameter, Point(0,0,thickness2));
  mSurfaces[2] = s;
  mCntSurfaces = 3;
}


//////////////////////////////////////////////////////////////////////
/// \param r1 radius of curvature surface 1
/// \param r2 radius of curvature surface 2
/// \param thickness thickness between surface 1 and 2
/// \param material Pointer to material 
/// \param diameter lens diameter
//////////////////////////////////////////////////////////////////////
void ElementWithSurfaces::standardLens(real r1, real r2, real thickness,
				       Material* const material, real diameter)
{
  SurfaceSpherical* s = new SurfaceSpherical(r1, diameter, Point(0,0,0));
  mSurfaces[0] = s;
  mMaterials[0] = material;
  s = new SurfaceSpherical(r2, diameter, Point(thickness,0,0));
  mSurfaces[1] = s;
  mCntSurfaces = 2;
}
