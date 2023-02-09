#include "read_line_to_vector.h"

int ReadLineToVector(FILE *fptr, vect_char *line) {
  line->size = 0;
  int c = 0, eof = 0;
  while (c != '\n' && (eof = (c = getc(fptr)) != EOF)) {
    vect_push_char(line, c);
  }
  vect_push_char(line, 0);

  return eof;
}
