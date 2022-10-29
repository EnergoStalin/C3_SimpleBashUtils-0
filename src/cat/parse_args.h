#ifndef SRC_CAT_PARSE_ARGS_H_
#define SRC_CAT_PARSE_ARGS_H_

#include "cat_config.h"
#include "return_code.h"

ReturnCode ParseArgs(int argc, char *const *argv, CatConfig *config);

#endif  // SRC_CAT_PARSE_ARGS_H_
