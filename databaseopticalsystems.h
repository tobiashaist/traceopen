////////////////////////////////////////////////////////////
///  \file databaseopticalsystems.h
///  \brief include file for class DatabaseOpticalSytems
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef DATABASEOPTICALSYSTEMS_HPP 
#define DATABASEOPTICALSYSTEMS_HPP

#include <iostream>
#include "database.h"
#include "entrydatabaseopticalsystems.h"



////////////////////////////////////////////////////////////
///  \brief stores optical systems (e.g. lenses or complete lenses)
////////////////////////////////////////////////////////////
///
/// Storing/Loading on external files have to be thought
/// in Detail about .... Not Simple !
///
/// Perhaps: vector is not the perfect container
/// because we actually might have lots of systems (10.000 if the
/// community helps and we have patents and manufacturers ....
/// Therefore: searching for the right lens might take lots of time
///   (on the other hand: That does not have to be fast)
/// And again on the other hand: For Materials it has to be not too
/// slow (perhaps) ....
///
/// Anyway: Generalization to the other databases (Materials, Coatings, BRDFs ...)
/// can we generalize that by a parent Database class ?
///
/// What do we have to be able for all Databases
/// 
/// addEntry
/// deleteEntry
/// search Entry By Name,
/// search Entry by index
/// load
/// save
/// 
///  \date 07.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class DatabaseOpticalSystems : public Database
{
    
 public:
  explicit DatabaseOpticalSystems(const std::string name);  ///< ctor
  ~DatabaseOpticalSystems(); ///dtor
  
  /// load and save to be done !
  
 protected:

};

#endif
