#ifndef SRC_CAT_RETURN_CODE_H_
#define SRC_CAT_RETURN_CODE_H_

typedef enum { OK, NO_FILE, INVALID_ARGUMENTS } ReturnCode;

const char *GetCodeName(ReturnCode code);

#endif  // SRC_CAT_RETURN_CODE_H_
