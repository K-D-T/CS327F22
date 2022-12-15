#include <stdio.h>

#include "queue.h"

int main(int argc, char *argv[])
{
  queue_t q;
  int i, j;
  
  queue_init(&q);

  for (i = 0; i < 100; i++) {
    queue_enqueue(&q, i);
  }

  printf("%d\n", queue_size(&q));

  for (i = 0; i < 50; i++) {
    queue_dequeue(&q, &j);
    printf("%d\n", j);
  }

  printf("%d\n", queue_size(&q));
  
  for (i = 0; i < 100; i++) {
    queue_enqueue(&q, i);
  }

  /*
  printf("%d\n", queue_size(&q));

  queue_deinit(&q);

  printf("%p %p %d\n", q.front, q.back, q.size);
  */
  
  // Infinite loop
  while (1) {
    queue_dequeue(&q, &j);
  }
  
  return 0;
}
