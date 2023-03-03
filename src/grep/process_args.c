#include "./process_args.h"

#include <getopt.h>

#include "../common/common_vectors.h"
#include "./process_file.h"

ReturnCode ProcessArgs(int argc, char *const *argv, GrepConfig *config) {
  ReturnCode return_code = OK;
  struct option long_option_struct[] = {
      {"regexp", required_argument, 0, 'e'},
      {"ignore-case", no_argument, 0, 'i'},
      {"invert-match", no_argument, 0, 'v'},
      {"count", no_argument, 0, 'c'},
      {"files-with-matches", no_argument, 0, 'l'},
      {"line-number", no_argument, 0, 'n'},
      {"no-filename", no_argument, 0, 'h'},
      {"no-messages", no_argument, 0, 's'},
      {"file", required_argument, 0, 'f'},
      {0, 0, 0, 0}};
  char *short_option_string = "e:ivclnhsf:";
  int long_option_id = 0, c = 0;

  vect_char_ptr *files = vect_init_char_ptr(1);

  while (return_code == OK && c != -1 && optind < argc) {
    if (argv[optind][0] != '-') {
      vect_push_char_ptr(files, argv[optind]);
      optind++;
    } else {
      c = getopt_long(argc, argv, short_option_string, long_option_struct,
                      &long_option_id);
      switch (c) {
        case 'e':
          config->regexp = optarg;
          break;
        case 'i':
          config->ignore_case = 1;
          break;
        case 'v':
          config->invert_match = 1;
          break;
        case 'c':
          if (!config->files_with_matches) {
            config->count = 1;
          }
          break;
        case 'l':
          config->files_with_matches = 1;
          config->count = 0;
          break;
        case 'n':
          config->number_lines = 1;
          break;
        case 'h':
          config->no_filename = 1;
          break;
        case 's':
          config->suppress_error = 1;
          break;
        case 'f':
          config->regexp_file = optarg;
          break;
      }
    }
  }

  if (files->size >= 1) {
    size_t i = 0;
    if (!config->regexp && !config->regexp_file) {
      config->pattern = vect_at_char_ptr(files, 0);
      i = 1;
      if (files->size == 2) {
        config->no_filename = 1;
      }
    } else if (files->size == 1) {
      config->no_filename = 1;
    }
    for (; i < files->size && return_code == OK; i++) {
      return_code = ProcessFile(vect_at_char_ptr(files, i), config);
      if (return_code == FILE_DONT_EXIST && config->suppress_error) {
        return_code = OK;
      }
    }
  } else {
    return_code = INVALID_ARGUMENTS;
  }

  vect_free(files);

  return return_code;
}
