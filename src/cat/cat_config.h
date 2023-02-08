#ifndef SRC_CAT_CAT_CONFIG_H
#define SRC_CAT_CAT_CONFIG_H

typedef struct {
  int verbose;
  int number_nonblank;
  int number_lines;
  int extra_symbols_endline;
  int extra_symbols_tabs;
  int squeeze_blank;
} CatConfig;

#endif /* SRC_CAT_CAT_CONFIG_H */
