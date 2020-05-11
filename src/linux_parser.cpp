#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <unistd.h>
#include <iterator>
#include "parser_helper.h"
#include "linux_parser.h"

using std::string;
using std::vector;

/*
  Parsing methods for System class
*/
// Read and return operating system name
string LinuxParser::OperatingSystem() {
    string line, key, value;
    std::ifstream filestream(kOSPath);
    if(filestream.is_open()) {
        while(std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ' ', '_');
            std::replace(line.begin(), line.end(), '=', ' ');
            std::replace(line.begin(), line.end(), '"', ' ');
            std::istringstream linestream(line);
            while(linestream >> key >> value) {
                if(key == "PRETTY_NAME") {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        } 
    }
    return value;
}

// Read and return kernel identifier information
string LinuxParser::Kernel() {
    string line, os, version, kernel_id;
    std::ifstream filestream(kProcDirectory + kVersionFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel_id;
    }
    return kernel_id;
}

// Read and return the system memory utilization
double LinuxParser::MemoryUtilization() {
    long memTotal = ParserHelper::GetValueByKey<long>("MemTotal:", kProcDirectory + kMeminfoFilename);
    long memFree = ParserHelper::GetValueByKey<long>("MemFree:", kProcDirectory + kMeminfoFilename);
    return (double)(memTotal - memFree) / memTotal;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    return ParserHelper::GetValueByKey<int>("processes", kProcDirectory + kStatFilename);
}

// Read and return the number of actively running processes
int LinuxParser::RunningProcesses() {
    return ParserHelper::GetValueByKey<int>("procs_running", kProcDirectory + kStatFilename);
}

// Read and return the system uptime (in sec)
long LinuxParser::UpTime() {
    return ParserHelper::GetValue<long>(kProcDirectory + kUptimeFilename);
}


/*
  Parsing methods for Processor class
*/
// Read and return CPU utilization (10 values)
vector<int> LinuxParser::CpuUtilization() {
    string line;
    int value;
    vector<int> cpu;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if(filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> line;
        while(linestream >> value)  cpu.push_back(value);
    }
    return cpu;
}


/*
  Parsing methods for Process class
*/
// Return integral directories in /proc/ as pids
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

// Retrieve cpu stats for a process used for calculating process cpu utilization and process uptime
std::vector<std::string> LinuxParser::ProcessCpuStat(int pid) {
    std::string line;
    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
    std::getline(filestream, line);
    std::istringstream linestream(line);
    std::istream_iterator<std::string> beg(linestream), end;
    std::vector<std::string> cpuStats(beg, end);
    return cpuStats;
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
    return ParserHelper::GetValueByKey<std::string>("Uid:", kProcDirectory + std::to_string(pid) + kStatusFilename);
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
    string uid = LinuxParser::Uid(pid);
    string line, user, x, fileUid;
    std::ifstream filestream(kPasswordPath);
    if(filestream.is_open()) {
        while(std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while(linestream >> user >> x >> fileUid) {
                if(fileUid == uid)  return user;
            }
        }
    }
    return user;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
    std::string cmd = ParserHelper::GetValue<std::string>(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
    if(cmd.size() > 25)  cmd = cmd.substr(0, 25) + "...";
    return cmd;
}

// Read and return the memory used by a process (in mb)
long LinuxParser::Ram(int pid) { 
    return ParserHelper::GetValueByKey<long>("VmData:", kProcDirectory + std::to_string(pid) + kStatusFilename);
}