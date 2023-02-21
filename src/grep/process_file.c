#include "./process_file.h"

#include <regex.h>

#include "../common/common_vectors.h"
#include "../common/vect.h"
#include "regex_helper.h"
#include "regex_vector.h"

ReturnCode ProcessFile(char *path, const GrepConfig *config) {
  ReturnCode return_code = OK;

  FILE *fptr = fopen(path, "r");

  if (fptr) {
    printf("%s\n", path);
    vect_regex_t_ptr *regexs = vect_init_regex_t_ptr(5);
    if ((return_code = MakeRegexes(config, regexs)) == OK) {
      int c = 0;
      while ((c = getc(fptr)) != EOF) {
        putc(c, stdout);
      }
    }
    fclose(fptr);
    vect_free_inner_ptrs_regex_t_ptr(regexs);
  } else {
    return_code = FILE_DONT_EXIST;
  }

  return return_code;
}
