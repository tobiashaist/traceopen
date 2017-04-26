////////////////////////////////////////////////////////////
/// \file databaseopticalsystems.cc
/// \brief class DatabaseOpticalSystems
///  \date 25.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#include "databaseopticalsystems.h"


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
DatabaseOpticalSystems::DatabaseOpticalSystems(const std::string name) :
  Database(name)
{
  ;
}

DatabaseOpticalSystems::~DatabaseOpticalSystems()
{
  // TODO: Do we have to delete here ?
  // to be thought about and checked
}
