#include "list.h"

extern list_t peep(list_t **head) {
  list_t value = {.value = 0.0, .priority = 0, .word = {'\0'}, .next = NULL};
  if (*head != NULL) {
    value = **head;
  }
  return value;
}
