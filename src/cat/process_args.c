#include "process_file.h"
#include "process_args.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "return_code.h"

ReturnCode ProcessArgs(int argc, char *const *argv, CatConfig *config) {
  ReturnCode return_code = OK;
  char *short_option_string = "+benstvTE";
  int long_option_id = 0;

  const struct option long_option_struct[] = {{"number-nonblank", no_argument, 0, 'b'},
                                        {"number", no_argument, 0, 'n'},
                                        {"squeeze-blank", no_argument, 0, 's'},
                                        {0, 0, 0, 0}};

  int c = 0;
  while (return_code == OK && c != -1 && optind < argc) {
    if(argv[optind][0] != '-') {
      optind++;
      continue;
    }
    c = getopt_long(argc, argv, short_option_string, long_option_struct,
                    &long_option_id);
    switch (c)
    {
    case 'b':
      config->number_nonblank = 1;
      break;
    case 'n':
      config->number_lines = 1;
      break;
    case 's':
      config->squeeze_blank = 1;
      break;
    case 'E':
      config->extra_symbols_endline = 1;
      break;
    case 'e':
      config->extra_symbols_endline = 1;
      config->verbose = 1;
      break;
    case 'T':
      config->extra_symbols_tabs = 1;
      break;
    case 't':
      config->extra_symbols_tabs = 1;
      config->verbose = 1;
      break;
    case 'v':
      config->verbose = 1;
      break;
    default:
      printf("%s", argv[long_option_id]);
      return_code = INVALID_ARGUMENTS;
      break;
    }
  }

  if(config->number_nonblank)
    config->number_lines = 0;

  size_t files_processed = 0;
  for (int i = 1; i < argc && return_code == OK; i++) {
    if(argv[i][0] == '-') continue;

    return_code = ProcessFile(argv[i], config);
    files_processed++;
  }
  if(!files_processed) {
    ProcessFile(0, config);
  }

  return return_code;
}
