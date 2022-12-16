#include <stdio.h>

#include "process_file.h"

#include "return_code.h"

#define FILE_BUFFER_SIZE 512

void ProcessBuffer(char buffer[FILE_BUFFER_SIZE], size_t actual_size, const CatConfig* config) {
  static char prev = '\n';

  for (size_t i = 0; i < actual_size; i++) {
    char curr = buffer[i];

    if (prev == '\n') {
      if (config->squeeze_blank) {
        static size_t nlines = 0;
        if(curr == '\n') {
          nlines++;
        } else {
          nlines = 0;
        }

        if (nlines > 1) {
          continue;
        }
      }

      if (config->number_nonblank && curr != '\n') {
        static size_t strings = 1;
        fprintf(stdout, "%6lu\t", strings++);
      }
      if(config->number_lines) {
        static size_t strings = 1;
        fprintf(stdout, "%6lu\t", strings++);
      }
    }

    if(curr == '\n') {
      if(config->extra_symbols_endline) {
        fputc('$', stdout);
      }
    } else if(curr == '\t') {
      if(config->extra_symbols_tabs) {
        fputs("^I", stdout);
        curr = 0;
      }
    }

    if(curr)
      fputc(curr, stdout);

    prev = buffer[i];
  }
}

ReturnCode ProcessFile(char *path, const CatConfig *config) {
  ReturnCode return_code = OK;

  char buffer[FILE_BUFFER_SIZE];

  FILE *file = path ? fopen(path, "r") : stdin;

  if(file) {
    size_t read;
    while ((read = fread(buffer, 1, FILE_BUFFER_SIZE, file)) != 0) {
      ProcessBuffer(buffer, read, config);
    }

    fclose(file);
  }
  else
  {
    return_code = NO_FILE;
  }

  return return_code;
}
