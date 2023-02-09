#ifndef SRC_GREP_REGEX_HELPER_H
#define SRC_GREP_REGEX_HELPER_H

#include <regex.h>

#include "../common/common_vectors.h"
#include "../common/return_code.h"
#include "grep_config.h"
#include "regex_vector.h"

#define IFFLAG(flag, value) ((flag) ? (value) : 0)

ReturnCode CompileRegexWithFlags(char *pattern, const GrepConfig *config,
                                 regex_t *reg);
ReturnCode ReadRegexesFromFile(char *file, const GrepConfig *config,
                               vect_regex_t_ptr *regexs);
ReturnCode MakeRegexes(const GrepConfig *config, vect_regex_t_ptr *regexs);
int CompileRegexFlags(const GrepConfig *config);

#endif /* SRC_GREP_REGEX_HELPER_H */
