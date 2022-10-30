#include <stdio.h>

#include "cat_config.h"
#include "parse_args.h"
#include "process_file.h"
#include "return_code.h"

int main(int argc, char* const* argv) {
  ReturnCode return_code = OK;
  CatConfig config = {0};
  if ((return_code = ParseArgs(argc, argv, &config)) == OK) {
    return_code = ProcessFile(&config);
  }

  if (return_code != OK) {
    printf("Something went wrong: %s\n", GetCodeName(return_code));
  }

  return return_code;
}
