#ifndef PROCESS_H
#define PROCESS_H

//#include "linux_parser.h"
#include <string>

using std::string;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // Done: See src/process.cpp
  std::string User();                      // Done: See src/process.cpp
  std::string Command();                   // Done: See src/process.cpp
  float CpuUtilization();                  // Done: See src/process.cpp
  std::string Ram();                       // Done: See src/process.cpp
  long int UpTime();                       // Done: See src/process.cpp
  bool operator<(Process const& a) const;  // Done: See src/process.cpp

  Process(int pid);  // See src/process.cpp

  // Done: Declare any necessary private members
 private:
 	int pid_;
 	string user_ = {};
 	string command_ = {};
};

#endif