#include "list.h"

extern list_t pop(list_t **head) {
  list_t *prev = NULL;
  list_t value = {.value = 0.0, .priority = 0, .word = {'\0'}, .next = NULL};
  if (*head != NULL) {
    value = **head;
    prev = *head;
    (*head) = (*head)->next;
    free(prev);
    prev = NULL;
  }
  return value;
}
