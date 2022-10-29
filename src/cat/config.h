#ifndef _SRC_CAT_CONFIG_H
#define _SRC_CAT_CONFIG_H

#include <stdbool.h>

typedef struct {
  char *file;
  bool verbose;
  bool number_nonblank;
  bool number_lines;
  bool extra_symbols;
  bool squeeze_blank;
} s_config;

#endif  //_SRC_CAT_CONFIG_H