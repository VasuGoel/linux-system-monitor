#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include "process.h"
#include "processor.h"

class System {
private:
    Processor cpu_;
    std::vector<Process> processes_;

public:
    Processor& Cpu();
    std::vector<Process>& Processes();

    std::string OperatingSystem();
    std::string Kernel();
    double MemoryUtilization();
    int TotalProcesses();
    int RunningProcesses();
    long UpTime();
};

#endif