#include "read_line_to_vector.h"

int ReadLineToVector(FILE *fptr, vect_char *line) {
  line->size = 0;
  int c = 0, eof = 0;
  while (c != '\n' && (eof = (c = getc(fptr)) != EOF)) {
    vect_push_char(line, c);
  }

  if (eof == EOF) {
    vect_push_char(line, 0);
  } else {
    line->data[line->size - 1] = 0;
  }

  return eof;
}
