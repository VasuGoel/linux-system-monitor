#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include "linux_parser.h"

class Processor {
private:
    std::vector<int> buffer_{0};
    double processorUtilization_;

public:
    double Utilization();
};

#endif