#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> cpu_processes = LinuxParser::CpuUtilization();
    float user = stof(cpu_processes[0]);
    float nice = stof(cpu_processes[1]);
    float system = stof(cpu_processes[2]);
    float idle = stof(cpu_processes[3]);
    float iowait = stof(cpu_processes[4]);
    float irq = stof(cpu_processes[5]);
    float softirq = stof(cpu_processes[6]);
    float steal = stof(cpu_processes[7]);
    
    float Idle = idle + iowait;
    float non_idle = user + nice + system + irq + softirq + steal;

    return non_idle / Idle; 
}