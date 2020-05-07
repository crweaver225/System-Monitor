#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int id) : pid(id) { }

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<int> process_numbers = LinuxParser::CpuUtilization(Pid());
    int utime = process_numbers[0];
    int stime = process_numbers[1];
    int cutime = process_numbers[2];
    int cstime = process_numbers[3];
    int starttime = process_numbers[4];
    float total_time = utime + stime;
    float seconds = LinuxParser::UpTime() - (starttime /  sysconf(_SC_CLK_TCK));
    if (seconds == 0) { return 0.0; }
    float cpu_usage =  100 * ((total_time / sysconf(_SC_CLK_TCK))/ seconds);
    cpuUtilization_ = cpu_usage;
    return cpu_usage; 
}

const float Process::getExistingCpuUtilization() const {
    return cpuUtilization_;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() {
    string memory = LinuxParser::Ram(Pid());
    if (memory.length() == 0) {
        return "";
    } else {
        return to_string(stoi(memory) / 1000);
    }
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {  return LinuxParser::UpTime() - (LinuxParser::UpTime(Pid()) / sysconf(_SC_CLK_TCK)); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {  return cpuUtilization_ > a.getExistingCpuUtilization(); }