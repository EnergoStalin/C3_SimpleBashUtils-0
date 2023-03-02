#include "read_line_to_vector.h"

#define LAST_VECT(v) (vect_at_char((v), ((v)->size - 1)))

int ReadLineToVector(FILE *fptr, vect_char *line) {
  line->size = 0;
  int c = 0;
  while (((c = getc(fptr)) != EOF) && (c != '\n')) {
    vect_push_char(line, c);
  }

  vect_push_char(line, 0);

  return c;
}
