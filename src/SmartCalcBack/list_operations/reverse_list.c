#include "list.h"

extern void reverse_list(list_t **head) {
  if (*head != NULL) {
    list_t *prev = NULL;
    list_t *next = (*head)->next;
    while (next != NULL) {
      (*head)->next = prev;
      prev = *head;
      *head = next;
      next = (*head)->next;
    }
    (*head)->next = prev;
  }
}
