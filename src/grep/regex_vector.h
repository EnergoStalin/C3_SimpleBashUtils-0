#ifndef SRC_GREP_REGEX_VECTOR_H
#define SRC_GREP_REGEX_VECTOR_H

#include <regex.h>

#include "../common/vect.h"

VECT_DECLARE_NAME(regex_t *, regex_t_ptr)
VECT_DECLARE_NESTED_PTR_FREE_FOR_NAME(regex_t_ptr)

#endif /* SRC_GREP_REGEX_VECTOR_H */
