#include <string>
#include <vector>
#include <algorithm>
#include "system.h"
#include "linux_parser.h"

/* 
    Return the system's CPU object
*/
Processor& System::Cpu() { return cpu_; }

/*
    Return a container composed of the system's processes
*/
// Compare function for two processes (based on ram usage)
bool compareProcess(Process &a, Process &b) { return a.Ram() > b.Ram(); }

std::vector<Process>& System::Processes() { 
    std::vector<Process> processes;
    std::vector<int> pids{LinuxParser::Pids()};
    for(auto pid: pids)  processes.push_back(Process(pid));
    std::sort(processes.begin(), processes.end(), compareProcess);
    processes_ = processes;
    return processes_;
}

/*
    Return system data
*/
// Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// Return the system's kernel identifier
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Return the system's memory utilization
double System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }
// Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }
// Return the number of seconds since the system started running
long System::UpTime() { return LinuxParser::UpTime(); }