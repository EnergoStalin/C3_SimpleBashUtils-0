#include "process_file.h"

#include "return_code.h"

ReturnCode ProcessFile(const CatConfig *config) {
  ReturnCode return_code = OK;

  if (config->file == 0) {
    return_code = NO_FILE;
  }

  return return_code;
}
