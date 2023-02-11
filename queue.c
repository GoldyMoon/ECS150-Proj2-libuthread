#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct queue {
	/* TODO Phase 1 */
	int size;
	node* head;
	node* end;
};

struct node {
	void *data
	struct node* next;
}

queue_t queue_create(void)
{
	/* TODO Phase 1 */
	queue_t queue = (queue_t)malloc(sizeof(struct queue));
	if (queue == NULL) {
		return NULL;
	}
	queue->size = 0;
	queue->head = NULL;
	queue->end = NULL;
	return queue;
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
