typedef struct queue_node queue_node_t;

struct queue_node {
  int data;
  queue_node_t *next;
};

typedef struct queue {
  struct queue_node *front, *back;
  int size;
} queue_t;

int queue_init(queue_t *q);
int queue_deinit(queue_t *q);
int queue_enqueue(queue_t *q, int data);
int queue_dequeue(queue_t *q, int *data);
int queue_front(queue_t *q, int *data);
int queue_size(queue_t *q);
int queue_is_empty(queue_t *q);
