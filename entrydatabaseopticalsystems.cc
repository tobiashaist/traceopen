////////////////////////////////////////////////////////////
/// \file entrydatabaseopticalsystems.cc
/// \brief class EntryDatabaseOpticalSystems
///  \date 25.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "entrydatabaseopticalsystems.h"


//////////////////////////////////////////////////////////////////////
/// \param system the optical system
//////////////////////////////////////////////////////////////////////
EntryDatabaseOpticalSystems::EntryDatabaseOpticalSystems(OpticalSystem* system) :
  mSystem(system)
{
  ;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
EntryDatabaseOpticalSystems::~EntryDatabaseOpticalSystems( )
{
  // TODO: We have to think if we create and destroy the optical
  // systems, material etc. in this class or outside !
}
