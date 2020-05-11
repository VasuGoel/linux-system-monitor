#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
    std::string Format(int s);
    std::string ElapsedTime(long times);
    std::string KbToMb(long memInKb);
};

#endif