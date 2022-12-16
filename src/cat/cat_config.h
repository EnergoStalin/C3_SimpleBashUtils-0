#ifndef SRC_CAT_CONFIG_H_
#define SRC_CAT_CONFIG_H_

typedef struct {
  int verbose;
  int number_nonblank;
  int number_lines;
  int extra_symbols_endline;
  int extra_symbols_tabs;
  int squeeze_blank;
} CatConfig;

#endif  // SRC_CAT_CONFIG_H_
