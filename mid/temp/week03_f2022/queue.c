#include <stdlib.h>

#include "queue.h"

int queue_init(queue_t *q)
{
  q->size = 0;
  q->front = q->back = NULL;
  
  return 0;
}

int queue_deinit(queue_t *q)
{
  queue_node_t *tmp;
  
  while (q->front) {
    tmp = q->front;
    q->front = q->front->next;
    free(tmp);
  }

  /* These two lines aren't necessary.  I consider them good style. */
  q->back = NULL;
  q->size = 0;
  
  return 0;
}

int queue_enqueue(queue_t *q, int data)
{
  if (q->size) {
    /* queue is not empty; add to tail */
    if (!(q->back->next = malloc(sizeof (*q->back->next)))) {
      return 1;
    }
    q->back = q->back->next;
  } else {
    /* queue is empty; add first node */

    /* sizeof is a compile-time operator that returns the size (in bytes) *
     * of the type of the given expression.                               */
    if (!(q->front = q->back = malloc(sizeof (*q->back)))) {
      return 1;
    }
    /* front and back are the same instance, so front->next is NULL, too! */
  }
  q->back->next = NULL;
  q->size++;
  q->back->data = data;
  
  return 0;
}

int queue_dequeue(queue_t *q, int *data)
{
  queue_node_t *tmp;
  
  if (q->front) {
    tmp = q->front;
    *data = q->front->data;
    q->front = q->front->next;
    q->size--;
    
    free(tmp);

    if (!q->front) {
      q->back = NULL;
    }
    
    return 0;
  }

  return 1;
}

int queue_front(queue_t *q, int *data)
{
  if (!q->front) {
    return 1;
  }

  *data = q->front->data;
  
  return 0;
}

int queue_size(queue_t *q)
{
  return q->size;
}

int queue_is_empty(queue_t *q)
{
  return !q->size;
}
