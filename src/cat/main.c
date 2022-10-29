#include <stdio.h>

#include "config.h"
#include "errors.h"
#include "parse_args.h"
#include "process_file.h"

int main(int argc, char* const* argv) {
  int ret_code = 0;
  s_config config;
  if ((ret_code = ParseArgs(argc - 1, argv + 1, &config)) == OK) {
    ret_code = ProcessFile(config);
  }

  return ret_code;
}