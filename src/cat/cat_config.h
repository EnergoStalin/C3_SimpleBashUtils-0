#ifndef SRC_CAT_CONFIG_H_
#define SRC_CAT_CONFIG_H_

#include <stdbool.h>

typedef struct {
  char *file;
  bool verbose;
  bool number_nonblank;
  bool number_lines;
  bool extra_symbols;
  bool squeeze_blank;
} CatConfig;

#endif  // SRC_CAT_CONFIG_H_
