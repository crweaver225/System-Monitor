#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

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
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  float mem_total;
  float mem_free;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        std::replace(key.begin(), key.end(), ' ', '_');
        std::replace(key.begin(), key.end(), ':', '_');
        if (key == "MemTotal_") {
          mem_total = stof(value);
        } else if (key == "MemFree_") {
          mem_free = stof(value);
        }
      }
    }
  }
  return mem_free / mem_total; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string upTime;
  string idleTime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while(linestream >> upTime >> idleTime) {
        return stol(upTime);
      }
    }
  }
  return 0; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  //vector<string> cpu_value;
  string key, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice, line;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
        std::replace(key.begin(), key.end(), ' ', '_');
        if (key == "cpu") {
           vector<string> cpu_values = {user, nice, system, idle, iowait, irq, softirq, steal, guest, guest};
           return cpu_values;
        }
      }
    }
  }
  return {}; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key;
  string value;
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        std::replace(key.begin(), key.end(), ' ', '_');
        if (key == "processes") {
          return stoi(value);
        }
      }
    }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key;
  string value;
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        std::replace(key.begin(), key.end(), ' ', '_');
        if (key == "procs_running") {
          return stoi(value);
        }
      }
    }
  }   
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    string line;
    while(std::getline(filestream, line)) {
      return line;
    }
  }
  return string(); 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
     string line;
    while (std::getline(filestream, line)) {
      string key;
      string value;
      std::istringstream linestream (line);
      while (linestream >> key >> value ) {
        if (key == "VmSize:") {
          return value;
        }
      }
    }
  }
  return string(); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::ifstream filestream(kProcDirectory + to_string(pid) + "/status");
  if (filestream.is_open()) {
    string line;
    while (std::getline(filestream, line)) {
      string key;
      string value;
      std::istringstream linestream (line);
      while (linestream >> key >> value ) {
        if (key == "Uid:") {
          std::ifstream filestream2(kPasswordPath);
          if (filestream2.is_open()) {
            string line2;
            while(std::getline(filestream2, line2)) {
              string delimiter = ":x:" + value;
              size_t pos;
             if ((pos = line2.find(delimiter)) != string::npos) {
              string token = line2.substr(0, pos);
              return token;
             }
            }
          }
          return value;
        }
      }
    }
  }
  return string(); 
}

vector<int> LinuxParser::CpuUtilization(int pid) {
  vector<int> cpu_values;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    string line;
    int index = 0;
    while(std::getline(filestream, line)) {
      std::istringstream stringstream(line);
      string line2;
      while (std::getline(stringstream, line2, ' ')) {
        if (index > 12 && index < 17) {
          cpu_values.push_back(stoi(line2));
        }
        if (index == 21) {
          cpu_values.push_back(stoi(line2));
        }
        index += 1;
      }
    }
  }
  return cpu_values;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
   std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    string line;
    int index = 0;
    while(std::getline(filestream, line)) {
      std::istringstream stringstream(line);
      string line2;
      while (std::getline(stringstream, line2, ' ')) {
        if (index == 21) {
          return stol(line2);
        }
        index += 1;
      }
    }
  }
  return 0; 
}