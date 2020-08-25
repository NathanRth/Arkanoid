#include "mtime.h"

using namespace std::chrono;

mtime_t getMTime()
{
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    return ms.count();
}