#define _GNU_SOURCE

#include "./process_file.h"

#include <ctype.h>
#include <regex.h>
#include <string.h>

#include "../common/common_vectors.h"
#include "../common/vect.h"
#include "read_line_to_vector.h"
#include "regex_helper.h"
#include "regex_vector.h"

typedef struct {
  const char *name;
  FILE *ptr;
  const GrepConfig *config;
} FileDescriptor;

void do_file(const FileDescriptor *fd, vect_regex_t_ptr *regexes) {
  vect_char *buffer = vect_init_char(250);
  size_t line_number = 0;
  size_t matches = 0;

  while (ReadLineToVector(fd->ptr, buffer) != EOF) {
    line_number++;

    int match = REG_NOMATCH;
    if (regexes->size > 0) {
      for (size_t i = 0; i < regexes->size && match == REG_NOMATCH; i++) {
        match = regexec(vect_at_regex_t_ptr(regexes, i), buffer->data,
                        (size_t)0, NULL, 0);
      }
    } else if (fd->config->pattern) {
      if (fd->config->ignore_case) {
        match = strcasestr(buffer->data, fd->config->pattern) != 0;
      } else {
        match = strstr(buffer->data, fd->config->pattern) != 0;
      }
      match = match ? !REG_NOMATCH : REG_NOMATCH;
    } else {
      match = !REG_NOMATCH;
    }

    if (fd->config->invert_match) {
      match = !match;
    }

    if (match != REG_NOMATCH) {
      matches++;

      if (!fd->config->count && !fd->config->files_with_matches) {
        if (!fd->config->no_filename) {
          printf("%s:", fd->name);
        }
        if (fd->config->number_lines) {
          printf("%lu:", line_number);
        }
        printf("%s", buffer->data);
      }
    }
  }

  if (fd->config->files_with_matches && matches > 0) {
    printf("%s\n", fd->name);
  } else {
    if (fd->config->count) {
      if (!fd->config->no_filename) {
        printf("%s:", fd->name);
      }
      printf("%lu\n", matches);
    }
  }

  vect_free(buffer);
}

ReturnCode ProcessFile(char *path, const GrepConfig *config) {
  ReturnCode return_code = OK;

  FILE *fptr = fopen(path, "r");
  FileDescriptor fd = {path, fptr, config};

  if (fptr) {
    vect_regex_t_ptr *regexes = vect_init_regex_t_ptr(5);
    if ((return_code = MakeRegexes(config, regexes)) == OK) {
      do_file(&fd, regexes);
    }
    fclose(fptr);
    vect_free_inner_ptrs_regex_t_ptr(regexes);
  } else {
    return_code = FILE_DONT_EXIST;
  }

  return return_code;
}
