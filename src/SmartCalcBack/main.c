#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "smart_calc.h"

int main(int argc, char **argv) {
  double result = 0;
  if (argc > 1 && argv[1] != NULL) {
    double value = 0;
    if (argv[2] != NULL) {
      value = atof(argv[2]);
    }
    result = smart_calc(argv[1], value);
    if (strcmp(argv[1], "Error\0")) {
      printf("%.7lf\n", result);
    } else {
      printf("%s\n", argv[1]);
    }
  }
  return 0;
}
