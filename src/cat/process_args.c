#include "process_args.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/common_vectors.h"
#include "../common/return_code.h"
#include "process_file.h"

ReturnCode ProcessArgs(int argc, char *const *argv, CatConfig *config) {
  ReturnCode return_code = OK;
  char *short_option_string = "+benstvTE";
  int long_option_id = 0;

  const struct option long_option_struct[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {0, 0, 0, 0}};

  vect_char_ptr *files = vect_init_char_ptr(1);

  int c = 0;
  while (return_code == OK && c != -1 && optind < argc) {
    if (argv[optind][0] != '-') {
      vect_push_char_ptr(files, argv[optind]);
      optind++;
    } else {
      c = getopt_long(argc, argv, short_option_string, long_option_struct,
                      &long_option_id);
      switch (c) {
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
          return_code = INVALID_ARGUMENTS;
          break;
      }
    }
  }

  if (config->number_nonblank) config->number_lines = 0;

  for (size_t i = 0; i < files->size && return_code == OK; i++) {
    return_code = ProcessFile(vect_at_char_ptr(files, i), config);
  }

  vect_free(files);

  return return_code;
}
