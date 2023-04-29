#include "operation_functions.h"

extern list_t *parser(char *argv, double x) {
  char *digits = "0123456789.\0";
  char *arithmetic_1 = "+-\0";
  char *arithmetic_2 = "*/\0";
  char *priority_4 = "^\0";
  const char *binary_operation[] = {"mod"};
  const char *unary_operation[] = {"cos",  "sin",  "tan", "acos", "asin",
                                   "atan", "sqrt", "ln",  "log"};
  char *priority_6 = "()\0";

  list_t *head = NULL;
  char c[256] = {'\0'};
  long double value = 0;
  int priority = 0;
  int len = strlen(argv);
  int unary_arr_len = sizeof unary_operation / sizeof unary_operation[0];
  int binary_arr_len = sizeof binary_operation / sizeof binary_operation[0];
  int flag = 0;
  for (int i = 0; i < len; ++i) {
    if (strchr(digits, argv[i])) {
      do {
        strncat(c, &argv[i], 1);
        ++i;
      } while (strchr(digits, argv[i]) && argv[i] != '\0');
      value = atof(c);
      memset(c, '\0', strlen(c));
      priority = digit;
      push(&head, value, c, priority);
      value = 0;
    }
    while (argv[i] >= 97 && argv[i] <= 122 && argv[i] != 'x') {
      do {
        strncat(c, &argv[i], 1);
        for (int j = 0; j < unary_arr_len && !flag; j++) {
          if (!strcmp(c, unary_operation[j])) {
            priority = func_unary;
            flag = 1;
          }
        }
        for (int j = 0; j < binary_arr_len && !flag; j++) {
          if (!strcmp(c, binary_operation[j])) {
            priority = func_binary;
            flag = 1;
          }
        }
        ++i;
      } while (!flag);
      push(&head, 0, c, priority);
      flag = 0;
      memset(c, '\0', strlen(c));
    }
    if (i < len) {
      if (strchr(digits, argv[i])) {
        do {
          strncat(c, &argv[i], 1);
          ++i;
        } while (strchr(digits, argv[i]) && argv[i] != '\0');
        value = atof(c);
        priority = digit;
        memset(c, '\0', strlen(c));
        --i;
      } else if (strchr(arithmetic_1, argv[i])) {
        if (head == NULL || head->word[0] == '(') {
          push(&head, 0, "\0", 0);
        }
        c[0] = argv[i];
        priority = arithm_1;
      } else if (strchr(arithmetic_2, argv[i])) {
        c[0] = argv[i];
        priority = arithm_2;
      } else if (strchr(priority_4, argv[i])) {
        c[0] = argv[i];
        priority = exponent;
      } else if (strchr(priority_6, argv[i])) {
        c[0] = argv[i];
        priority = bracket;
      } else if (argv[i] == 'x') {
        sprintf(c, "%.2lf", x);
        value = atof(c);
        priority = digit;
        memset(c, '\0', strlen(c));
      }
      push(&head, value, c, priority);
      c[0] = '\0';
      value = 0;
    }
  }
  return head;
}
