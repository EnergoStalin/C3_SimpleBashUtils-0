#ifndef SRC_GREP_PROCESS_FILE_H_
#define SRC_GREP_PROCESS_FILE_H_

#include <regex.h>

#include "../common/return_code.h"
#include "grep_config.h"

#define IFFLAG(flag, value) ((flag) ? (value) : 0)

ReturnCode ProcessFile(char *path, const GrepConfig *config);

#endif  // SRC_GREP_PROCESS_FILE_H_
