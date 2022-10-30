#include "parse_args.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "return_code.h"

static void AllocateAndPrepareOptions(char **short_option_string,
                                      struct option **long_option_struct) {
  *long_option_struct = calloc(4, sizeof(struct option));
  struct option *o = *long_option_struct;

  o->name = "number-nonblank";
  o->has_arg = 0;
  o->flag = NULL;
  o->val = 'b';

  o++;
  o->name = "number";
  o->has_arg = 0;
  o->flag = NULL;
  o->val = 'n';

  o++;
  o->name = "squeeze-blank";
  o->has_arg = 0;
  o->flag = NULL;
  o->val = 's';

  *short_option_string = "+benstvTE";
}

static ReturnCode ValidateConfig(const CatConfig *config) {
  ReturnCode return_code = OK;

  if (config->file == 0) {
    return_code = NO_FILE;
  }

  return return_code;
}

ReturnCode ParseArgs(int argc, char *const *argv, CatConfig *config) {
  ReturnCode return_code = OK;
  char *short_option_string = NULL;
  struct option *long_option_struct = NULL;
  int long_option_id = 0;

  AllocateAndPrepareOptions(&short_option_string, &long_option_struct);

  int c = 0;
  while ((c = getopt_long(argc, argv, short_option_string, long_option_struct,
                          &long_option_id)) != -1 &&
         return_code == OK) {
    printf("%c\n", c);
    switch (c) {
      case 'b':
        config->number_nonblank = 1;
        break;

      default:
        return_code = INVALID_ARGUMENTS;
        break;
    }
  }
  free(long_option_struct);

  if (return_code == OK) {
    return_code = ValidateConfig(config);
  }

  return return_code;
}
