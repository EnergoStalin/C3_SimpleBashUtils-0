#ifndef SRC_CAT_PROCESS_ARGS_H_
#define SRC_CAT_PROCESS_ARGS_H_

#include "../common/return_code.h"
#include "cat_config.h"

ReturnCode ProcessArgs(int argc, char *const *argv, CatConfig *config);

#endif  // SRC_CAT_PROCESS_ARGS_H_
