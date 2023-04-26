#ifndef LIST_OPERATIONS_LIST_H_
#define LIST_OPERATIONS_LIST_H_

#include <stdlib.h>
#include <string.h>

typedef struct list_t {
  long double value;
  char word[7];
  int priority;
  struct list_t *next;
} list_t;

extern void push(list_t **head, double value, char *word, int priority);
extern list_t pop(list_t **head);
extern list_t peep(list_t **head);
extern void free_list(list_t **head);
extern void reverse_list(list_t **head);

#endif  // LIST_OPERATIONS_LIST_H_
