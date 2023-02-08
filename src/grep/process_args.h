#ifndef SRC_GREP_PROCESS_ARGS_H_
#define SRC_GREP_PROCESS_ARGS_H_

#include "../common/return_code.h"
#include "grep_config.h"

ReturnCode ProcessArgs(int argc, char *const *argv, GrepConfig *config);

#endif  // SRC_GREP_PROCESS_ARGS_H_
