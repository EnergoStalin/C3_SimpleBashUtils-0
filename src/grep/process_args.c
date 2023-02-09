#include "./process_args.h"

#include <getopt.h>

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
      {"only-matching", no_argument, 0, 'o'},
      {0, 0, 0, 0}};
  char *short_option_string = "e:ivclnhsf:o";
  int long_option_id = 0, c = 0;

  while (optind < argc) {
    while (return_code == OK &&
           (c = getopt_long(argc, argv, short_option_string, long_option_struct,
                            &long_option_id)) != -1) {
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
          config->count = 1;
          break;
        case 'l':
          config->files_with_matches = 1;
          break;
        case 'n':
          config->number_lines = 1;
          break;
        case 'h':
          config->no_filename = 1;
          break;
        case 's':
          config->no_filename = 1;
          break;
        case 'f':
          config->regexp_file = optarg;
          break;
        case 'o':
          config->only_matching = 1;
          break;
      }
    }
    return_code = ProcessFile(argv[optind++], config);
  }

  return return_code;
}
