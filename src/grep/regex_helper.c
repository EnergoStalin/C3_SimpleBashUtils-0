#include "regex_helper.h"

#include "read_line_to_vector.h"

ReturnCode CompileRegexWithFlags(char *regexp, const GrepConfig *config,
                                 regex_t *reg) {
  ReturnCode return_code = OK;
  if (regcomp(reg, regexp, CompileRegexFlags(config)) != 0) {
    return_code = INVALID_ARGUMENTS;
  }

  return return_code;
}

ReturnCode ReadRegexesFromFile(char *file, const GrepConfig *config,
                               vect_regex_t_ptr *regexs) {
  ReturnCode return_code = OK;

  FILE *fptr = fopen(file, "r");
  if (fptr) {
    vect_char *line = vect_init_char(2);
    while (ReadLineToVector(fptr, line) != EOF && return_code == OK) {
      if (line->size == 1U) {
        continue;
      }

      regex_t *reg = calloc(sizeof(regex_t), 1);
      if (CompileRegexWithFlags(line->data, config, reg) == OK) {
        vect_push_regex_t_ptr(regexs, reg);
      } else {
        free(reg);
      }
    }
    fclose(fptr);
    vect_free(line);
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
  return IFFLAG(config->ignore_case, REG_ICASE) | REG_NOSUB | REG_EXTENDED;
}
