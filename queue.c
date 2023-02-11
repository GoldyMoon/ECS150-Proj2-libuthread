#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct node{
  int value;
  struct nodes* next;
};

struct queue {
	/* TODO Phase 1 */
  int head;
  int end;
  struct nodes* queuelist;
};

queue_t queue_create(void)
{
	/* TODO Phase 1 */
  queue_t temp;
  temp->queuelist = (struct node*) malloc (sizeof(struct node));
  return temp;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
}
