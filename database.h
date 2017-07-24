////////////////////////////////////////////////////////////
///  \file database.h
///  \brief include file for class Database
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef DATABASE_HPP 
#define DATABASE_HPP

#include <iostream>
#include "entrydatabase.h"
#include <vector>
#include <memory>


////////////////////////////////////////////////////////////
///  \brief Databases for (systems, materials, BRDFs, Coatings etc.). Abstract Base class
////////////////////////////////////////////////////////////
///
/// The Database consists of Entries. And the Entries are just different
/// for the different Databases. 
///
/// Storing/Loading on external files have to be thought
/// in Detail about .... Not Simple !
///
/// Static Polymorphism actually would be good enough here
/// On the other hand, dynamic polymorphism does not cost
/// us much here ... so go here without templates...
///
/// Perhaps: vector is not the perfect container
/// because we actually might have lots of e.g. systems (10.000 if the
/// community helps and we have patents and manufacturers ....
/// Therefore: searching for the right lens might take lots of time
///   (on the other hand: That does not have to be fast)
/// And again on the other hand: For Materials it has to be not too
/// slow (perhaps) ....
///
///
/// What do we have to be able for all Databases
/// 
/// addEntry
/// deleteEntry
/// search Entry By Name,
/// search Entry by index
/// search based on complex things (like in Zemax)
/// load
/// save
/// 
///  \date 25.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
// TODO: More or less everything ! Also concerning entries and also concerning
// the general concept and the implementation for OpticalSystems, Materials
class Database
{
    
 public:
  explicit Database(const std::string databasename);  ///< ctor
  virtual ~Database() = 0;
  
 protected:
  std::string mName;                                            ///< Name of Database
  std::vector<std::unique_ptr<EntryDatabase>> mEntries;         ///< all our entries
  int mCntEntries;                                              ///< Number of systems
};

#endif
