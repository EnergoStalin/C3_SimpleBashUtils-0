#include <stdio.h>

#include "../common/return_code.h"
#include "./grep_config.h"
#include "./process_args.h"

int main(int argc, char **argv) {
  ReturnCode return_code = OK;
  GrepConfig config = {0};

  return_code = ProcessArgs(argc, argv, &config);

  if (return_code != OK) {
    printf("ERROR: %s\n", GetCodeName(return_code));
  }

  return return_code;
}
