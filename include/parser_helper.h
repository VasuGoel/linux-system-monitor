#ifndef PARSER_HELPER_H
#define PARSER_HELPER_H

#include <string>

// Contains helper functions for easing the operation of LinuxParser
namespace ParserHelper {
    template<typename T> T GetValue(std::string const &path) {
        T value;
        std::string line;
        std::ifstream filestream(path);
        if(filestream.is_open()) {
            std::getline(filestream, line);
            std::istringstream linestream(line);
            linestream >> value;
        }
        return value;
    };

    template<typename T> T GetValueByKey(std::string const &filter, std::string const &path) {
        T value;
        std::string line, key;
        std::ifstream filestream(path);
        if(filestream.is_open()) {
            while(std::getline(filestream, line)) {
                std::istringstream linestream(line);
                while(linestream >> key >> value) {
                    if(key == filter)  return value;
                }
            }
        }
        return value;
    };
};

#endif