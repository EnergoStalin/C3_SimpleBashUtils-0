#include "regex_vector.h"

void free_regex_ptr(regex_t *ptr) {
  regfree(ptr);
  free(ptr);
}

VECT_GENERATE_NAME(regex_t *, regex_t_ptr)
VECT_GENERATE_NESTED_PTR_FREE_FOR_NAME(regex_t_ptr, free_regex_ptr)
