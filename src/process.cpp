#include <string>
#include <unistd.h>
#include "process.h"

// Constructor
Process::Process(int pid) {
    pid_ = pid;
    std::vector<std::string> cpuStats = LinuxParser::ProcessCpuStat(pid);
    utime_ = std::stof(cpuStats[13]);
    stime_ = std::stof(cpuStats[14]);
    cutime_ = std::stof(cpuStats[15]);
    cstime_ = std::stof(cpuStats[16]);
    starttime_ = std::stof(cpuStats[21]);
    HERTZ_ = sysconf(_SC_CLK_TCK);
}

// Return this process's ID
int Process::Pid() { return pid_; }

// Return the user (name) that generated this process
std::string Process::User() { return LinuxParser::User(pid_); }

// Return this process's average CPU utilization since its start
double Process::CpuUtilization() { 
    long uptime = LinuxParser::UpTime();
    long total_time = utime_ + stime_ + cutime_ + cstime_;
    double seconds = uptime - (double)(starttime_ / HERTZ_);
    double utilization = ((double)(total_time / HERTZ_) / seconds);
    return (utilization > 1) ? 1 : utilization;
}

// Return this process's memory utilization
long Process::Ram() { return LinuxParser::Ram(pid_); }

// Return the age of this process (in seconds)
long int Process::UpTime() {
    long uptime = LinuxParser::UpTime();
    return uptime - (starttime_ / HERTZ_);
}

// Return the command that generated this process
std::string Process::Command() { return LinuxParser::Command(pid_); }