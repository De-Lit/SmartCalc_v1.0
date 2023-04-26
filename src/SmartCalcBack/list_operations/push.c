#include "list.h"

extern void push(list_t **head, double value, char *word, int priority) {
  list_t *tmp = (list_t *)malloc(sizeof(list_t));
  tmp->value = value;
  memset(tmp->word, '\0', sizeof(tmp->word));
  strcat(tmp->word, word);
  tmp->priority = priority;
  tmp->next = (*head);
  (*head) = tmp;
}
