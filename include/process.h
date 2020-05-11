#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"

class Process {
private:
    int pid_;
    float utime_;
    float stime_;
    float cutime_;
    float cstime_;
    float starttime_;
    int HERTZ_;     // clock ticks per second

public:
    Process(int pid);
    int Pid();
    std::string User();
    double CpuUtilization();
    long Ram();
    long int UpTime();
    std::string Command();
};

#endif