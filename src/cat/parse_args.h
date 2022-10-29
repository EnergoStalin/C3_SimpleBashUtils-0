#ifndef SRC_CAT_PARSE_ARGS_H_
#define SRC_CAT_PARSE_ARGS_H_

#include "cat_config.h"
#include "return_code.h"

RETURN_CODE ParseArgs(int argc, char *const *argv, s_config *config);

#endif  // SRC_CAT_PARSE_ARGS_H_
