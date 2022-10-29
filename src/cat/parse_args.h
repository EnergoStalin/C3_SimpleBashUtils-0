#ifndef _SRC_CAT_PARSE_ARGS_H
#define _SRC_CAT_PARSE_ARGS_H

#include "config.h"
#include "errors.h"

ERROR_CODE ParseArgs(int argc, char *const *argv, s_config *config);

#endif  //_SRC_CAT_PARSE_ARGS_H