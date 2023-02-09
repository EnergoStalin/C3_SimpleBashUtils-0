#include "return_code.h"

const char *GetCodeName(ReturnCode code) {
  static const char *kReturnCodeDescriptions[] = {
      [OK] = "OK",
      [NO_FILE] = "No file provided.",
      [INVALID_ARGUMENTS] = "Invalid arguments provided.",
      [FILE_DONT_EXIST] = "File don't exist."};

  return kReturnCodeDescriptions[code];
}
