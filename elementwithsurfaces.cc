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
ElementWithSurfaces::ElementWithSurfaces() : mCntSurfaces(0)
{
  ELOG("CTOR Element With Surfaces");
}

//////////////////////////////////////////////////////////////////////
ElementWithSurfaces::ElementWithSurfaces(ElementWithSurfaces& e) 
{
  ELOG("COPY CTOR Element With Surfaces, #surfaces = ", static_cast<int>(e.mSurfaces.size()));
  // here, we cannot just copy the mSurfaces because that would
  // just (try to) copy the pointers.
  // Since these are unique pointers, it is anyway not
  // allowed (and it would not make sense even if it would be)
  //
  // The same, of course, for Materials
  // We actually have to perform a deep copy here !

  //mSurfaces= e.mSurfaces;   
  //  mMaterials = e.mMaterials;

  for(int t=0; t < e.mSurfaces.size(); ++t)
    {
      e.mSurfaces[t].get()->show();
      addSurface(e.mSurfaces[t].get(), e.mMaterials[t]);
    }
  mCntSurfaces = e.mCntSurfaces;
}

//////////////////////////////////////////////////////////////////////
ElementWithSurfaces::~ElementWithSurfaces()
{
  ELOG("DTOR Element With Surfaces");

}

//////////////////////////////////////////////////////////////////////
/// \param nr Surface number
/// We need that for addElement within OpticalSystem
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
  ELOG("ElementWithSurfaces::getSurface",surfacenumber);

  return mSurfaces[surfacenumber].get();
}

//////////////////////////////////////////////////////////////////////
/// \param s Pointer to surface
/// \param m Pointer to material
//////////////////////////////////////////////////////////////////////
void ElementWithSurfaces::addSurface(Surface* const s,  Material* const m)
{
#if 1
  ELOG("addSurface");
  Surface* sc = s->copy();   // for lens this points to a newly created Lens !
  mSurfaces.push_back(move(s->mSmartPtrSurface));  
  //  std::cerr << "Number of Elements in mElements = " << mElements.size() << std::endl;

  mMaterials.push_back(m);
  mCntSurfaces++;

  //  return mSurfaces.size();
#endif
}


////////////////////////////////////////////////////////////
void ElementWithSurfaces::show()
{
  Element::show();  // parent
  
  ELOG("SHOW ELEMENTWITHSURFACES: number of Surfaces", mCntSurfaces);
  for(int t=0; t < mCntSurfaces; ++t)
    mSurfaces[t]->show();
  
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
#if 1
  SurfaceSpherical* s = new SurfaceSpherical(r1, diameter, Point(0,0,0));
  addSurface(s,m1);

  s = new SurfaceSpherical(r2, diameter, Point(0,0,thickness1));
  addSurface(s,m2);

  s = new SurfaceSpherical(r3, diameter, Point(0,0,thickness2));
  addSurface(s,m2);

  mCntSurfaces = 3;
#endif
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
#if 1
  ELOG("standard lens");
  SurfaceSpherical* s = new SurfaceSpherical(r1, diameter, Point(0,0,0));
  addSurface(s, material);

  s = new SurfaceSpherical(r2, diameter, Point(0,0,thickness));
  //  LOG("Thickness = ", thickness);
  addSurface(s, material);
  mCntSurfaces = 2;
#endif
}

////////////////////////////////////////////////////////////
/// \return pointer to Material
////////////////////////////////////////////////////////////
Material* ElementWithSurfaces::getMaterial(int index)
{
  return mMaterials[index];
}

////////////////////////////////////////////////////////////
/// \return surface position z
////////////////////////////////////////////////////////////
real ElementWithSurfaces::getZPosition(int index)
{
  return mSurfaces[index]->getPosition()->getZ().get();
}


////////////////////////////////////////////////////////////
/// \param surface pointer to the surface
////////////////////////////////////////////////////////////
ElementWithSurfaces& ElementWithSurfaces::operator=(ElementWithSurfaces& element) 
{
  ElementWithSurfaces temp(element);
  swap(element);
  return* this;
}

////////////////////////////////////////////////////////////
void ElementWithSurfaces::swap(ElementWithSurfaces& element) 
{
  std::swap(mCntSurfaces, element.mCntSurfaces);
  std::swap(mSurfaces, element.mSurfaces);
  std::swap(mMaterials, element.mMaterials);
}
