#include "parse_args.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "return_code.h"

RETURN_CODE ParseArgs(int argc, char *const *argv, s_config *config) {
  RETURN_CODE ret_code = OK;
  int c, longid;
  struct option longopts;

  const char *optstring =
      "b-W number-nonblank evEn -W number s -W squeeze-blank tT";
  while ((c = getopt_long(argc, argv, optstring, &longopts, &longid)) != -1) {
    printf("%s", longopts.name);
    if (strcmp(longopts.name, "b") == 0) {
      config->number_nonblank = true;
    }
  }

  return ret_code;
}
