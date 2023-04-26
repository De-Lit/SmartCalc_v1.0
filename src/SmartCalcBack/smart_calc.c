#include "smart_calc.h"

#include "./operation_functions/operation_functions.h"

extern double smart_calc(char *argv, double x) {
  double result = 0;
  if (strlen(argv)) {
    int error = 0;
    error = validator(argv);
    if (error) {
      memset(argv, '\0', strlen(argv));
      strcat(argv, "Error\0");
    } else {
      list_t *head = parser(argv, x);
      reverse_list(&head);
      head = calculate_station(head);
      result = head->value;
      free_list(&head);
    }
  }
  return result;
}
