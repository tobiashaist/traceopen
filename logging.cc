#include <iostream>
#include "logging.h"

void tloggerprint(std::string s)
{
  std::string time_str;
  time_t raw_time;
  time( & raw_time );
  time_str = ctime( &raw_time );


  std::cerr <<    time_str.substr( 0 , time_str.size() - 1 ) << " " << s << std::endl;
}

void tloggerprint(std::string s, int n)
{
  std::string time_str;
  time_t raw_time;
  time( & raw_time );
  time_str = ctime( &raw_time );


  std::cerr <<    time_str.substr( 0 , time_str.size() - 1 ) << " " << s << " ... " << n << std::endl;
}

void tloggerprint(std::string s, double n)
{
  std::string time_str;
  time_t raw_time;
  time( & raw_time );
  time_str = ctime( &raw_time );
  std::cerr << time_str.substr( 0 , time_str.size() - 1 ) << " " << s << " ... " << n << std::endl;
}

void tloggerprint(std::string s, double n1, double n2, double n3)
{
  std::string time_str;
  time_t raw_time;
  time( & raw_time );
  time_str = ctime( &raw_time );
  std::cerr << time_str.substr( 0 , time_str.size() - 1 ) << " " << s << " ... " << n1 << " " << n2 << "  "<< n3<<std::endl;
}

void tloggerprint(std::string s, double n1, double n2)
{
  std::string time_str;
  time_t raw_time;
  time( & raw_time );
  time_str = ctime( &raw_time );
  std::cerr << time_str.substr( 0 , time_str.size() - 1 ) << " " << s << " ... " << n1 << " " << n2  <<std::endl;
}

void tloggerprint(std::string s, double n, double n2, double n3, double n4)
{
  std::string time_str;
  time_t raw_time;
  time( & raw_time );
  time_str = ctime( &raw_time );
  std::cerr << time_str.substr( 0 , time_str.size() - 1 ) << " " <<s << " ... " << n << " " << n2 << "  "<< n3 << "  " << n4 <<std::endl;
}


