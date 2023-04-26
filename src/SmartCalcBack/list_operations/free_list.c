#include "list.h"

extern void free_list(list_t **head) {
  list_t *prev = NULL;
  while (*head != NULL) {
    prev = *head;
    (*head) = (*head)->next;
    free(prev);
  }
}
