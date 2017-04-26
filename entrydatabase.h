////////////////////////////////////////////////////////////
///  \file entrydatabase.h
///  \brief include file for class DatabaseOpticalSytems
///  \date 07.04.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Institute of Applied Optics, University of Stuttgart ITO 
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 

#ifndef ENTRYDATABASE_HPP 
#define ENTRYDATABASE_HPP

#include <iostream>

////////////////////////////////////////////////////////////
///  \brief stores/manages one Entry in the Database. Abstract Base class.
////////////////////////////////////////////////////////////
///
///  \date 25.4.2017
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
class EntryDatabase
{
    
 public:
  EntryDatabase();  ///< ctor
  virtual ~EntryDatabase() = 0;
  
  /// load and save to be done !
  
 protected:

};

#endif
