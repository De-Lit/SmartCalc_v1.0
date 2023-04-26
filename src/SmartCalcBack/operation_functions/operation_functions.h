#ifndef OPERATION_FUNCTIONS_OPERATION_FUNCTIONS_H_
#define OPERATION_FUNCTIONS_OPERATION_FUNCTIONS_H_

#include <stdio.h>

#include "../list_operations/list.h"

enum type_t {
  digit = 0,
  arithm_1 = 1,
  arithm_2 = 2,
  func_binary = 2,
  exponent = 3,
  func_unary = 4,
  bracket = 7
};

extern int validator(char *argv);
extern list_t *parser(char *argv, double x);
extern list_t *calculate_station(list_t *infix_head);

#endif  // OPERATION_FUNCTIONS_OPERATION_FUNCTIONS_H_
