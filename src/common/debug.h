#ifndef SRC_COMMON_DEBUG_H
#define SRC_COMMON_DEBUG_H

#include <stdio.h>

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define FLOGF(_FILE, FORMAT, ...) \
  fprintf(_FILE, __FILE__ " - " LINE_STRING ": " FORMAT, __VA_ARGS__)

#define LOGF(FORMAT, ...) FLOGF(stdout, FORMAT, __VA_ARGS__)

#endif  // SRC_COMMON_DEBUG_H
