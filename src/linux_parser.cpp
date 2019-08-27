#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"
#include<iostream>

using std::stoi;
using std::stol;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string key;
  string line, value;
  float total_mem, free_mem; 
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {
        total_mem = stoi(value);
      }

      else if (key == "MemFree:"){
        free_mem = stoi(value);
        break;
      }
    }

  }
  return ((total_mem - free_mem) / total_mem); 
}

// Done: Read and return the system uptime
long LinuxParser::UpTime() { 
  string value;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  return stol(value); 
}

// Done: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  //LinuxParser::CPUStates states;
  long total {0};
  vector<string> cpu_utilization;
  cpu_utilization = LinuxParser::CpuUtilization();
  for (int state = kUser_; state  <= kSteal_; state++){
    total += stol(cpu_utilization[state]);
  }
  return total;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// Done: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  long active = LinuxParser::Jiffies() - LinuxParser::IdleJiffies();

  return active; 
}

// Done: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  long total {0};
  vector<string> cpu_utilization = LinuxParser::CpuUtilization();
  for (int state = kIdle_; state <= kIOwait_; state++){
    total += stol(cpu_utilization[state]);
  }
  return total;
}

// Done: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, info;
  vector<string> infos;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  // Get first line
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    // Tokenize
    while (std::getline(linestream, info, ' ')) {
      if ((info == "cpu") || (info == "")){
        continue;
      }
      infos.push_back(info);
    }
  }
  return infos;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line, key, value;
  vector<string> infos;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      /*std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return stoi(value);
        }
      }*/
      if (line.find("processes") != string::npos){
        return stoi(line.substr(line.find(" ") + 1));
      }
    }
  }
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line, key, value;
  vector<string> infos;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      if (line.find("procs_running") != string::npos){
        return stoi(line.substr(line.find(" ") + 1));
      }
    }
  }
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }