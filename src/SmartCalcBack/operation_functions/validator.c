#include "operation_functions.h"

enum symbol {
  START,
  DIGIT,
  X,
  UNARY_OPERATION,
  BINARY_OPERATION,
  DECUMAL,
  OPEN_BRACKET,
  CLOSE_BRACKET,
  UNARY_OPERATION_WORD,
  BINARY_OPERATION_WORD,
};

typedef struct pars {
  char c;
  int c_type;
  char c_last;
  int c_last_type;
  int bracket_count;
  int decimal_flag;
  int null_flag;
  int word_flag;
  char word[5];
  int error;
} pars;

static void is_valid_word_unary(pars *pars);
static void is_valid_word_binary(pars *pars);

extern int validator(char *argv) {
  pars pars = {0};
  char *unary_operation = "+-\0";
  char *binary_operation = "+-*/^\0";
  char *digits = "0123456789\0";
  for (int i = 0; argv[i] != '\0' && !pars.error; i++) {
    pars.c = argv[i];
    switch (pars.c_last_type) {
      case START:
        if (strchr(digits, pars.c)) {
          pars.c_type = DIGIT;
          if (pars.c == '0') {
            pars.null_flag = 1;
          }
        } else if (pars.c == 'x') {
          pars.c_type = X;
        } else if (strchr(unary_operation, pars.c)) {
          pars.c_type = UNARY_OPERATION;
        } else if (pars.c == '(') {
          pars.c_type = OPEN_BRACKET;
          pars.bracket_count++;
        } else {
          is_valid_word_unary(&pars);
        }
        break;
      case DIGIT:
        if (strchr(digits, pars.c)) {
          pars.c_type = DIGIT;
          if (pars.null_flag == 1) {
            pars.error = 1;
          }
        } else if (strchr(binary_operation, pars.c)) {
          pars.c_type = BINARY_OPERATION;
          pars.decimal_flag = 0;
          pars.null_flag = 0;
        } else if (pars.c == '.' && pars.decimal_flag == 0) {
          pars.c_type = DECUMAL;
          pars.decimal_flag = 1;
        } else if (pars.c == ')') {
          pars.c_type = CLOSE_BRACKET;
          pars.bracket_count--;
          pars.decimal_flag = 0;
        } else {
          is_valid_word_binary(&pars);
        }
        break;
      case X:
        if (strchr(binary_operation, pars.c)) {
          pars.c_type = BINARY_OPERATION;
          pars.decimal_flag = 0;
          pars.null_flag = 0;
        } else if (pars.c == ')') {
          pars.c_type = CLOSE_BRACKET;
          pars.bracket_count--;
          pars.decimal_flag = 0;
        } else {
          is_valid_word_binary(&pars);
        }
        break;
      case UNARY_OPERATION:  // unary
        if (strchr(digits, pars.c)) {
          pars.c_type = DIGIT;
          if (pars.c == '0') {
            pars.null_flag = 1;
          }
        } else if (pars.c == 'x') {
          pars.c_type = X;
        } else if (pars.c == '(') {
          pars.c_type = OPEN_BRACKET;
          pars.bracket_count++;
        } else {
          is_valid_word_unary(&pars);
        }
        break;
      case BINARY_OPERATION:  // binary
        if (strchr(digits, pars.c)) {
          pars.c_type = DIGIT;
          if (pars.c == '0') {
            pars.null_flag = 1;
          }
        } else if (pars.c == 'x') {
          pars.c_type = X;
        } else if (pars.c == '(') {
          pars.c_type = OPEN_BRACKET;
          pars.bracket_count++;
        } else {
          is_valid_word_unary(&pars);
        }
        break;
      case DECUMAL:  // decimal
        if (strchr(digits, pars.c)) {
          pars.c_type = DIGIT;
          pars.null_flag = 0;
        } else if (strchr(binary_operation, pars.c)) {
          pars.c_type = BINARY_OPERATION;
          pars.decimal_flag = 0;
          pars.null_flag = 0;
        } else if (pars.c == ')') {
          pars.c_type = CLOSE_BRACKET;
          pars.bracket_count--;
          pars.decimal_flag = 0;
        } else {
          is_valid_word_binary(&pars);
        }
        break;
      case OPEN_BRACKET:  // '('
        if (strchr(digits, pars.c)) {
          pars.c_type = DIGIT;
        } else if (pars.c == 'x') {
          pars.c_type = X;
        } else if (strchr(unary_operation, pars.c)) {
          pars.c_type = UNARY_OPERATION;
        } else if (pars.c == '(') {
          pars.c_type = OPEN_BRACKET;
          pars.bracket_count++;
        } else {
          is_valid_word_unary(&pars);
        }
        break;
      case CLOSE_BRACKET:  // ')'
        if (strchr(binary_operation, pars.c)) {
          pars.c_type = BINARY_OPERATION;
        } else if (pars.c == ')') {
          pars.c_type = CLOSE_BRACKET;
          pars.bracket_count--;
        } else {
          is_valid_word_binary(&pars);
        }
        break;
      case UNARY_OPERATION_WORD:  // '[:alpha:]' unary
        if (pars.word_flag == 1) {
          is_valid_word_unary(&pars);
        } else if (pars.c == '(') {
          pars.c_type = OPEN_BRACKET;
          pars.bracket_count++;
        } else {
          pars.error = 1;
        }
        break;
      case BINARY_OPERATION_WORD:  // '[:alpha:]' binary
        if (pars.word_flag == 1) {
          is_valid_word_binary(&pars);
        } else if (pars.c == 'x') {
          pars.c_type = X;
        } else if (strchr(digits, pars.c)) {
          pars.c_type = DIGIT;
          if (pars.c == '0') {
            pars.null_flag = 1;
          }
        } else if (pars.c == '(') {
          pars.c_type = OPEN_BRACKET;
          pars.bracket_count++;
        } else {
          is_valid_word_unary(&pars);
        }
        break;
    }
    if (pars.bracket_count < 0) {
      pars.error = 1;
    } else {
      pars.c_last = pars.c;
      pars.c_last_type = pars.c_type;
    }
  }
  if (pars.error == 0) {
    if (pars.bracket_count != 0) {
      pars.error = 1;
    } else {
      switch (pars.c_last_type) {
        case DIGIT:
          break;
        case X:
          break;
        case CLOSE_BRACKET:
          break;
        case DECUMAL:
          break;
        default:
          pars.error = 1;
      }
    }
  }
  return pars.error;
}

static void is_valid_word_unary(pars *pars) {
  const char *word_operations[] = {"cos",  "sin",  "tan", "acos", "asin",
                                   "atan", "sqrt", "ln",  "log"};
  int flag = 0;
  int arr_len = sizeof word_operations / sizeof word_operations[0];
  strcat(pars->word, &pars->c);
  for (int i = 0; i < arr_len && flag == 0; i++) {
    if (strlen(pars->word) <= strlen(word_operations[i])) {
      if (!memcmp(pars->word, word_operations[i], strlen(pars->word))) {
        flag = 1;
        pars->word_flag = 1;
        pars->c_type = UNARY_OPERATION_WORD;
        if (strlen(pars->word) == strlen(word_operations[i])) {
          pars->word_flag = 0;
          memset(pars->word, '\0', strlen(pars->word));
        }
      }
    }
  }
  if (!flag) {
    pars->error = 1;
  }
}

static void is_valid_word_binary(pars *pars) {
  const char *word_operations[] = {"mod"};
  int flag = 0;
  int arr_len = sizeof word_operations / sizeof word_operations[0];
  strcat(pars->word, &pars->c);
  for (int i = 0; i < arr_len && flag == 0; i++) {
    if (strlen(pars->word) <= strlen(word_operations[i])) {
      if (!memcmp(pars->word, word_operations[i], strlen(pars->word))) {
        flag = 1;
        pars->word_flag = 1;
        pars->c_type = BINARY_OPERATION_WORD;
        if (strlen(pars->word) == strlen(word_operations[i])) {
          pars->word_flag = 0;
          pars->decimal_flag = 0;
          memset(pars->word, '\0', strlen(pars->word));
        }
      }
    }
  }
  if (!flag) {
    pars->error = 1;
  }
}
