#ifndef SRC_CAT_PROCESS_FILE_H
#define SRC_CAT_PROCESS_FILE_H

#include "../common/return_code.h"
#include "cat_config.h"

ReturnCode ProcessFile(char *path, const CatConfig *config);

#endif /* SRC_CAT_PROCESS_FILE_H */
