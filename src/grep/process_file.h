#ifndef SRC_GREP_PROCESS_FILE_H
#define SRC_GREP_PROCESS_FILE_H

#include <regex.h>

#include "../common/return_code.h"
#include "grep_config.h"

ReturnCode ProcessFile(char *path, const GrepConfig *config);

#endif /* SRC_GREP_PROCESS_FILE_H */
