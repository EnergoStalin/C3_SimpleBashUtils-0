#ifndef SRC_CAT_RETURN_CODE_H_
#define SRC_CAT_RETURN_CODE_H_

enum RETURN_CODE { OK };

const char *get_code_name(enum RETURN_CODE code) {
  static const char *RETURN_CODE_NAMES[] = {[OK] = "OK"};

  return RETURN_CODE_NAMES[code];
}

#endif  // SRC_CAT_RETURN_CODE_H_
