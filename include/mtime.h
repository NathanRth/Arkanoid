#ifndef TIME_H_
#define TIME_H_

#include <iostream>
#include <chrono>

// using alias
using mtime_t = int64_t;

// return current time in milliseconds
mtime_t getMTime();

#endif