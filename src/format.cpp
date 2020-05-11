#include <string>
#include <sstream>
#include <iomanip>
#include "format.h"

// Utility function to pad time units with 0 if value less than 10
std::string Format::Format(int s) {
    return (s >= 10) ? std::to_string(s) : std::string(1, '0') + std::to_string(s);
}

// Fucntion to convert time (in second) to HH:MM:SS
std::string Format::ElapsedTime(long seconds) {
    std::string secs = Format(seconds%60);
    std::string mins = Format((seconds/60)%60);
    std::string hrs = Format((seconds/3600)%24);
    std::string time = hrs + ":" + mins + ":" + secs;
    return time;
}

// Function to convert memory (in kilobyte) to megabyte
std::string Format::KbToMb(long memInKb) {
    float mb = (float)memInKb / 1024;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << mb;
    return stream.str();
}