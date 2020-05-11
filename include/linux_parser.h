#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <string>
#include <vector>

namespace LinuxParser {
    // Paths
    const std::string kProcDirectory{"/proc/"};
    const std::string kCmdlineFilename{"/cmdline"};
    const std::string kCpuinfoFilename{"/cpuinfo"};
    const std::string kStatusFilename{"/status"};
    const std::string kStatFilename{"/stat"};
    const std::string kUptimeFilename{"/uptime"};
    const std::string kMeminfoFilename{"/meminfo"};
    const std::string kVersionFilename{"/version"};
    const std::string kOSPath{"/etc/os-release"};
    const std::string kPasswordPath{"/etc/passwd"};

    // System
    std::string OperatingSystem();
    std::string Kernel();
    double MemoryUtilization();
    int TotalProcesses();
    int RunningProcesses();
    long UpTime();
    std::vector<int> Pids();

    // CPU
    std::vector<int> CpuUtilization();

    // Processes
    std::vector<std::string> ProcessCpuStat(int pid);
    std::string Uid(int pid);
    std::string User(int pid);
    std::string Command(int pid);
    long Ram(int pid);
};

#endif