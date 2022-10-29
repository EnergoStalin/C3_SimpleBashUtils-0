#ifndef SRC_CAT_RETURN_CODE_H_
#define SRC_CAT_RETURN_CODE_H_

typedef enum { OK } ReturnCode;

const char *GetCodeName(ReturnCode code) {
  static const char *kReturnCodeNames[] = {[OK] = "OK"};

  return kReturnCodeNames[code];
}

#endif  // SRC_CAT_RETURN_CODE_H_
