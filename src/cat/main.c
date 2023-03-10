#include <stdio.h>

#include "../common/return_code.h"
#include "cat_config.h"
#include "process_args.h"

int main(int argc, char *const *argv) {
  ReturnCode return_code = OK;
  CatConfig config = {0};

  return_code = ProcessArgs(argc, argv, &config);

  if (return_code != OK && return_code != INVALID_ARGUMENTS) {
    printf("ERROR: %s\n", GetCodeName(return_code));
  }

  return return_code;
}
