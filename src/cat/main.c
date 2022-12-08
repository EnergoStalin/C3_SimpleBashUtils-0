#include <stdio.h>

#include "cat_config.h"
#include "parse_args.h"
#include "process_file.h"
#include "return_code.h"

#ifdef DEBUG
#include "debug.h"
#endif

int main(int argc, char* const* argv) {
  ReturnCode return_code = OK;
  CatConfig config = {0};
  #ifdef DEBUG
    LOGF("%s", "Programm started.\n");
#endif

  if ((return_code = ParseArgs(argc, argv, &config)) == OK) {

#ifdef DEBUG
    LOGF(
      "\nConfig: %s - %s\n%s - %d\n%s - %d\n%s - %d\n%s - %d\n%s - %d\n",
      "file", config.file,
      "verbose", config.verbose,
      "number_nonblank", config.number_nonblank,
      "number_lines", config.number_lines,
      "extra_symbols", config.extra_symbols,
      "squeeze_blank", config.squeeze_blank
    );
#endif

    return_code = ProcessFile(&config);
  }

  if (return_code != OK) {
    printf("Something went wrong: %s\n", GetCodeName(return_code));
  }

  return return_code;
}
