////////////////////////////////////////////////////////////
///  \file entrydatabaseopticalsystems.h
///  \brief include file for class DatabaseOpticalSytems
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef ENTRYDATABASEOPTICALSYSTEMS_HPP 
#define ENTRYDATABASEOPTICALSYSTEMS_HPP

#include <iostream>
#include "entrydatabase.h"
#include "opticalsystem.h"

////////////////////////////////////////////////////////////
///  \brief stores/manages one optical systems in the Databse
////////////////////////////////////////////////////////////
///
///  \date 25.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class EntryDatabaseOpticalSystems : public EntryDatabase
{
    
 public:
  explicit EntryDatabaseOpticalSystems(OpticalSystem* system);  ///< ctor
  virtual ~EntryDatabaseOpticalSystems();

  /// load and save to be done !
  
 protected:
  OpticalSystem* mSystem;                       ///< the optical system to be stored

};

#endif
