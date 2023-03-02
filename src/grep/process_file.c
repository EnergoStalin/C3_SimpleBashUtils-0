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

static inline void print_match(const FileDescriptor *fd, size_t line_number,
                               vect_char *buffer) {
  if (!fd->config->count && !fd->config->files_with_matches) {
    if (!fd->config->no_filename) {
      printf("%s:", fd->name);
    }
    if (fd->config->number_lines) {
      printf("%lu:", line_number);
    }

    printf("%s\n", buffer->data);
  }
}

static inline void print_summary(const FileDescriptor *fd, size_t matches) {
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
}

static inline int do_regex_match(vect_regex_t_ptr *regexes, vect_char *buffer) {
  int match = REG_NOMATCH;
  for (size_t i = 0; i < regexes->size && match == REG_NOMATCH; i++) {
    match = regexec(vect_at_regex_t_ptr(regexes, i), buffer->data, (size_t)0,
                    NULL, 0);
  }
  return match;
}

static inline int do_pattern_match(const FileDescriptor *fd,
                                   vect_char *buffer) {
  int match = REG_NOMATCH;
  if (fd->config->ignore_case) {
    match = strcasestr(buffer->data, fd->config->pattern) != 0;
  } else {
    match = strstr(buffer->data, fd->config->pattern) != 0;
  }
  return match ? !REG_NOMATCH : REG_NOMATCH;
}

static inline void do_file(const FileDescriptor *fd,
                           vect_regex_t_ptr *regexes) {
  vect_char *buffer = vect_init_char(250);
  size_t line_number = 0;
  size_t matches = 0;
  int match = REG_NOMATCH;

  while (ReadLineToVector(fd->ptr, buffer) != EOF || buffer->size > 1) {
    line_number++;

    if (regexes->size > 0) {
      match = do_regex_match(regexes, buffer);
    } else if (fd->config->pattern) {
      match = do_pattern_match(fd, buffer);
    } else {
      match = !REG_NOMATCH;
    }

    if (fd->config->invert_match) {
      match = !match;
    }

    if (match != REG_NOMATCH) {
      matches++;

      print_match(fd, line_number, buffer);
    }
  }

  print_summary(fd, matches);

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
