#ifndef SRC_CAT_cat_config_H_
#define SRC_CAT_cat_config_H_

typedef struct {
  char *file;
  int verbose;
  int number_nonblank;
  int number_lines;
  int extra_symbols;
  int squeeze_blank;
} CatConfig;

#endif  // SRC_CAT_cat_config_H_
