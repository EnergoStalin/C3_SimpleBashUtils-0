#ifndef SRC_GREP_GREP_CONFIG_H
#define SRC_GREP_GREP_CONFIG_H

typedef struct {
  char *pattern;
  char *regexp;            // -e
  int ignore_case;         // -i
  int invert_match;        // -v
  int count;               // -c
  int files_with_matches;  // -l
  int number_lines;        // -n

  int no_filename;     // -h
  int suppress_error;  // -s
  char *regexp_file;   // -f
  int only_matching;   // -o
} GrepConfig;

#endif /* SRC_GREP_GREP_CONFIG_H */
