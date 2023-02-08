#include "./process_file.h"

#include <regex.h>

#include "../common/common_vectors.h"
#include "../common/vect.h"
#include "regex_vector.h"

int read_line_to_vector(FILE *fptr, vect_char *line) {
  char c;
  int eof = 0;
  while (!(eof = feof(fptr)) && c != '\n') {
    c = getc(fptr);
    if (c == '\n') {
      vect_push_char(line, 0);
    } else {
      vect_push_char(line, c);
    }
  }

  return !eof;
}

int compile_regex_flags(const GrepConfig *config) {
  return IFFLAG(config->ignore_case, REG_ICASE);
}

ReturnCode compile_regex_with_flags(char *pattern, const GrepConfig *config,
                                    regex_t *reg) {
  ReturnCode return_code = OK;
  if (regcomp(reg, pattern, compile_regex_flags(config)) != 0) {
    return_code = INVALID_ARGUMENTS;
  }

  return return_code;
}

ReturnCode read_regexes_from_file(char *file, const GrepConfig *config,
                                  vect_regex_t_ptr *regexs) {
  ReturnCode return_code = OK;

  FILE *fptr = fopen(file, "r");
  if (fptr) {
    vect_char *line = vect_init_char(256);
    while (read_line_to_vector(fptr, line) && return_code == OK) {
      regex_t *reg = malloc(sizeof(regex_t));
      if (compile_regex_with_flags(line->data, config, reg) == OK) {
        vect_push_regex_t_ptr(regexs, reg);
        line->size = 0;
      }
    }
    vect_free(line);
  } else {
    return_code = NO_FILE;
  }

  return return_code;
}

ReturnCode make_regexes(const GrepConfig *config, vect_regex_t_ptr *regexs) {
  ReturnCode return_code = OK;
  if (config->regexp) {
    regex_t *reg = malloc(sizeof(regex_t));
    if ((return_code = compile_regex_with_flags(config->regexp, config, reg)) ==
        OK) {
      vect_push_regex_t_ptr(regexs, reg);
    }
  } else if (config->regexp_file) {
    return_code = read_regexes_from_file(config->regexp_file, config, regexs);
  }

  return return_code;
}

ReturnCode ProcessFile(char *path, const GrepConfig *config) {
  ReturnCode return_code = OK;

  vect_regex_t_ptr *regexs = vect_init_regex_t_ptr(50);

  if ((return_code = make_regexes(config, regexs)) == OK) {
  }

  vect_free_inner_ptrs_regex_t_ptr(regexs);

  return return_code && path;
}
