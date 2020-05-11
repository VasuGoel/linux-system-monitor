#include <vector>
#include "processor.h"

// Return the active Cpu utilization within each sec
double Processor::Utilization() {
    std::vector<int> cpu = LinuxParser::CpuUtilization();
    
    long prevIdle = buffer_[3] + buffer_[4];
    long Idle = cpu[3] + cpu[4];

    long prevNonIdle = buffer_[0] + buffer_[1] + buffer_[2] + buffer_[5] + buffer_[6] + buffer_[7];
    long NonIdle = cpu[0] + cpu[1] + cpu[2] + cpu[5] + cpu[6] + cpu[7];

    long prevTotal = prevIdle + prevNonIdle;
    long Total = Idle + NonIdle;

    long totald = Total - prevTotal;
    long idled = Idle - prevIdle;
    
    processorUtilization_ = (double)(totald - idled) / totald;
    buffer_ = cpu;
    return processorUtilization_;
}