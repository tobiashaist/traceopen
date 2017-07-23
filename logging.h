/// Set LOGGING to 1 if you want logging
/// Set EXTREMELOGGING to 1 if you want logging also for ELOG macro (slow)
/// set LOGFILE to 1 if you want the LOGGING into traceopen.log instead of cerr

#ifndef LOGGING

// -------------------------------------------------
// PLEASE DEFINE THE FOLLOWING
#define LOGGING 1
#define EXTREMELOGGING 1
#define LOGFILE 0
// -------------------------------------------------

// Not very nice, not very professional but it works for our purpose.
// Can be very much improved
// T. Haist, April 2017
//
// We use variadic arguments

#if LOGGING
#define LOG(...) tloggerprint(__VA_ARGS__) 
#else
#define LOG(...)
#endif

#if EXTREMELOGGING
#define ELOG(...) tloggerprint(__VA_ARGS__) 
#else
#define ELOG(...)
#endif


  
void tloggerprint(std::string s);
void tloggerprint(std::string s, int n);
void tloggerprint(std::string s, double n);
void tloggerprint(std::string s, double n1, double n2);
void tloggerprint(std::string s, double n1, double n2, double n3);
void tloggerprint(std::string s, double n, double n2, double n3, double n4);

#endif


// EXAMPLE USAGE
//
//
// #include <iostream>
// #include <string>
// #include "logging.h"

// int main()
// {

// #if LOGFILE
//   freopen( "traceopen.log", "w", stderr );
// #endif

//   LOG("Starting the application..");
//   LOG("Starting the application..", 3);
//   LOG("Starting the application..", 3.2);
//   LOG("Starting the application..", 1.2, 3.2);
//   LOG("Starting the application..", 1.2, 3.3, 3.2);
//   LOG("Starting the application..", 7.2, 1.2, 3.3, 3.2);
//   return 0;
// }
