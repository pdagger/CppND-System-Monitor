#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Constructor for Process class
Process::Process(int pid){ 
  	pid_= pid;
  	command_ = LinuxParser::Command(pid_);
  	ram_ =  LinuxParser::Ram(pid_);
  	user_ = LinuxParser::User(pid_);
  	uptime_ = LinuxParser::UpTime(pid_);
  	cpu_utilization_ = (float)LinuxParser::ActiveJiffies(pid_) / ((float)LinuxParser::UpTime() - (float)uptime_ * sysconf(_SC_CLK_TCK));
  };

// Done: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_utilization_; }

// DONE: Return the command that generated this process
string Process::Command() { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() { return ram_; }

// Done: Return the user (name) that generated this process
string Process::User() { return user_; }

// Done: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }