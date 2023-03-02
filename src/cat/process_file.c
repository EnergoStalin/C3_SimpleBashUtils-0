#include "process_file.h"

#include <stdio.h>

#include "../common/return_code.h"

static inline size_t count_blank(int curr) {
  static size_t nlines = 0;
  if (curr == '\n') {
    nlines++;
  } else {
    nlines = 0;
  }

  return nlines;
}

static inline void number_nonblank(int curr) {
  if (curr != '\n') {
    static size_t count = 1;
    fprintf(stdout, "%6lu\t", count++);
  }
}

static inline void number_lines(int prev) {
  static size_t count = 1;
  if (prev == '\n') {
    count++;
  }
  fprintf(stdout, "%6lu\t", count);
}

static inline int verbose(int curr, const CatConfig *config) {
  int put = 1;
  if (curr >= 32) {
    if (curr < 127) {
      putchar(curr);
    } else if (curr == 127) {
      putchar('^');
      putchar('?');
    } else {
      putchar('M');
      putchar('-');
      if (curr >= 128 + 32) {
        if (curr < 128 + 127) {
          putchar(curr - 128);
        } else {
          putchar('^');
          putchar('?');
        }
      } else {
        putchar('^');
        putchar(curr - 128 + 64);
      }
    }
    put = 0;
  } else if (curr == '\t' && !config->extra_symbols_tabs) {
    putchar('\t');
    put = 0;
  } else if (curr != '\n') {
    putchar('^');
    putchar(curr + 64);
    put = 0;
  } else if (config->extra_symbols_endline) {
    putchar('$');
  }

  return put;
}

ReturnCode ProcessFile(char *path, const CatConfig *config) {
  ReturnCode return_code = OK;

  FILE *fd = path ? fopen(path, "r") : stdin;

  if (fd) {
    static int first = 1;
    static int prev = 0;
    int curr = 0;
    while ((curr = fgetc(fd)) != EOF) {
      int put = 1;
      if (prev == '\n' || first) {
        first = 0;
        if (config->squeeze_blank) {
          if (count_blank(curr) > 1) {
            continue;
          }
        }

        if (config->number_nonblank) {
          number_nonblank(curr);
        }
        if (config->number_lines) {
          number_lines(prev);
        }
      }

      if (config->verbose) {
        put = verbose(curr, config);
      }

      if(put) {
        putchar(curr);
      }
      prev = curr;
    }
    fclose(fd);
  } else {
    return_code = NO_FILE;
  }

  return return_code;
}
