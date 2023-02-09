#include "regex_helper.h"

#include "read_line_to_vector.h"

ReturnCode CompileRegexWithFlags(char *pattern, const GrepConfig *config,
                                 regex_t *reg) {
  ReturnCode return_code = OK;
  if (regcomp(reg, pattern, CompileRegexFlags(config)) != 0) {
    return_code = INVALID_ARGUMENTS;
  }

  return return_code;
}

ReturnCode ReadRegexesFromFile(char *file, const GrepConfig *config,
                               vect_regex_t_ptr *regexs) {
  ReturnCode return_code = OK;

  FILE *fptr = fopen(file, "r");
  if (fptr) {
    vect_char *line = vect_init_char(256);
    while (ReadLineToVector(fptr, line) && return_code == OK) {
      regex_t *reg = calloc(sizeof(regex_t), 1);
      if (CompileRegexWithFlags(line->data, config, reg) == OK) {
        vect_push_regex_t_ptr(regexs, reg);
      }
    }
    vect_free(line);
    // fclose(fptr);
  } else {
    return_code = FILE_DONT_EXIST;
  }

  return return_code;
}

ReturnCode MakeRegexes(const GrepConfig *config, vect_regex_t_ptr *regexs) {
  ReturnCode return_code = OK;
  if (config->regexp) {
    regex_t *reg = calloc(sizeof(regex_t), 1);
    if ((return_code = CompileRegexWithFlags(config->regexp, config, reg)) ==
        OK) {
      vect_push_regex_t_ptr(regexs, reg);
    }
  } else if (config->regexp_file) {
    return_code = ReadRegexesFromFile(config->regexp_file, config, regexs);
  }

  return return_code;
}

int CompileRegexFlags(const GrepConfig *config) {
  return IFFLAG(config->ignore_case, REG_ICASE);
}
