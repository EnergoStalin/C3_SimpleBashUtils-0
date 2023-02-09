#include "regex_vector.h"

VECT_GENERATE_NAME(regex_t *, regex_t_ptr)
VECT_GENERATE_NESTED_PTR_FREE_FOR_NAME(regex_t_ptr, regfree)
