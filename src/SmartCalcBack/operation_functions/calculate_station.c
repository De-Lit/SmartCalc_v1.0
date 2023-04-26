#include <math.h>

#include "operation_functions.h"

static void calculation(list_t **result_head, list_t **operations_head);

extern list_t *calculate_station(list_t *infix_head) {
  list_t null_list = {
      .value = 0.0, .priority = 0, .word = {'\0'}, .next = NULL};
  list_t *operations_head = NULL;
  list_t *result_head = NULL;
  list_t tmp;
  list_t operation;
  while (infix_head != NULL) {
    tmp = pop(&infix_head);
    if (tmp.priority == 0) {
      push(&result_head, tmp.value, tmp.word, tmp.priority);
    } else {
      if (operations_head == NULL) {
        push(&operations_head, tmp.value, tmp.word, tmp.priority);
      } else {
        if (tmp.word[0] == '(') {
          push(&operations_head, tmp.value, tmp.word, tmp.priority);
        } else if (tmp.word[0] == ')') {
          operation = peep(&operations_head);
          while (operation.word[0] != '(') {
            calculation(&result_head, &operations_head);
            operation = peep(&operations_head);
          }
          pop(&operations_head);
        } else {
          operation = peep(&operations_head);
          while (operation.priority >= tmp.priority &&
                 operation.word[0] != '(') {
            calculation(&result_head, &operations_head);
            if (operations_head != NULL) {
              operation = peep(&operations_head);
            } else {
              operation = null_list;
            }
          }
          push(&operations_head, tmp.value, tmp.word, tmp.priority);
        }
      }
    }
  }
  while (operations_head != NULL) {
    calculation(&result_head, &operations_head);
  }
  return result_head;
}

static void calculation(list_t **result_head, list_t **operations_head) {
  list_t a;
  list_t b;
  list_t result = {0};
  list_t operation = {0};
  operation = pop(operations_head);
  if (operation.word[0] == '+') {
    b = pop(result_head);
    a = pop(result_head);
    result.value = a.value + b.value;
    push(result_head, result.value, result.word, result.priority);
  } else if (operation.word[0] == '-') {
    b = pop(result_head);
    a = pop(result_head);
    result.value = a.value - b.value;
    push(result_head, result.value, result.word, result.priority);
  } else if (operation.word[0] == '*') {
    b = pop(result_head);
    a = pop(result_head);
    result.value = a.value * b.value;
    push(result_head, result.value, result.word, result.priority);
  } else if (operation.word[0] == '/') {
    b = pop(result_head);
    a = pop(result_head);
    result.value = a.value / b.value;
    push(result_head, result.value, result.word, result.priority);
  } else if (operation.word[0] == '^') {
    b = pop(result_head);
    a = pop(result_head);
    result.value = pow(a.value, b.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "mod") == 0) {
    b = pop(result_head);
    a = pop(result_head);
    result.value = fmod(a.value, b.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "cos") == 0) {
    a = pop(result_head);
    result.value = cos(a.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "sin") == 0) {
    a = pop(result_head);
    result.value = sin(a.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "tan") == 0) {
    a = pop(result_head);
    result.value = tan(a.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "acos") == 0) {
    a = pop(result_head);
    result.value = acos(a.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "asin") == 0) {
    a = pop(result_head);
    result.value = asin(a.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "atan") == 0) {
    a = pop(result_head);
    result.value = atan(a.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "sqrt") == 0) {
    a = pop(result_head);
    result.value = sqrt(a.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "ln") == 0) {
    a = pop(result_head);
    result.value = log(a.value);
    push(result_head, result.value, result.word, result.priority);
  } else if (strcmp(operation.word, "log") == 0) {
    a = pop(result_head);
    result.value = log10(a.value);
    push(result_head, result.value, result.word, result.priority);
  }
}
