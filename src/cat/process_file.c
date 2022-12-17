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

static inline void number_lines() {
  static size_t count = 1;
  fprintf(stdout, "%6lu\t", count++);
}

static inline void verbose(int curr) {
  if ((curr >= 0 && curr < 9) || (curr > 10 && curr <= 31)) {
    putchar('^');
    curr += 64;
  }
  if (curr == 127) {
    putchar('^');
    curr = '?';
  }
  if (curr >= 128 && curr <= 159) {
    puts("M-^");
    curr -= 64;
  }
  if (curr >= 160 && curr <= 255) {
    puts("M-");
    curr -= 128;
  }
}

static inline void extra_symbols(int *curr, const CatConfig *config) {
  if (*curr == '\n') {
    if (config->extra_symbols_endline) {
      fputc('$', stdout);
    }
  } else if (*curr == '\t') {
    if (config->extra_symbols_tabs) {
      fputs("^I", stdout);
      *curr = 0;
    }
  }
}

ReturnCode ProcessFile(char *path, const CatConfig *config) {
  ReturnCode return_code = OK;

  FILE *fd = path ? fopen(path, "r") : stdin;

  if (fd) {
    int prev = '\n';
    int curr = 0;
    while ((curr = fgetc(fd)) != EOF) {
      if (prev == '\n') {
        if (config->squeeze_blank) {
          if (count_blank(curr) > 1) {
            continue;
          }
        }

        if (config->number_nonblank) {
          number_nonblank(curr);
        }
        if (config->number_lines) {
          number_lines();
        }
      }

      extra_symbols(&curr, config);

      if (config->verbose) {
        verbose(curr);
      }

      putchar(curr);
      prev = curr;
    }
    fclose(fd);
  } else {
    return_code = NO_FILE;
  }

  return return_code;
}
