#include <stdio.h>

#include "cat_config.h"
#include "parse_args.h"
#include "process_file.h"
#include "return_code.h"

int main(int argc, char* const* argv) {
  int ret_code = 0;
  CatConfig config;
  if ((ret_code = ParseArgs(argc - 1, argv + 1, &config)) == OK) {
    ret_code = ProcessFile(config);
  }

  return ret_code;
}
