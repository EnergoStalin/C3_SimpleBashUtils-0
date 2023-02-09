#ifndef SRC_COMMON_RETURN_CODE_H
#define SRC_COMMON_RETURN_CODE_H

typedef enum {
  OK,
  NO_FILE,
  FILE_DONT_EXIST,
  PERMISSION_ERROR,
  INVALID_ARGUMENTS
} ReturnCode;

const char *GetCodeName(ReturnCode code);

#endif /* SRC_COMMON_RETURN_CODE_H */
