#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct queue {
	/* TODO Phase 1 */
	int size;
	node* head;
	node* tail;
};

struct node {
	void *data;
	struct node* next;
};

queue_t queue_create(void)
{
	/* TODO Phase 1 */
	queue_t queue = (queue_t)malloc(sizeof(struct queue));
	if (queue == NULL) {
		return NULL;
	}
	queue->size = 0;
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
	if (queue == NULL || queue->size != 0) {
		return -1;
	}
	free(queue);
	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if (data == NULL || queue == NULL) {
		return -1;
	}
	struct node* node = (struct node*)malloc(sizeof(struct node));
	if (node == NULL) {
		return -1;
	}
	node->data = data;
	node->next = NULL;
	if (queue->size == 0) {
		queue->size++;
		queue->head = queue->tail = node;
	} else {
		queue->size++;
		queue->tail->next = node;
		queue->tail = node;
	}
	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
	queue->size--;
	*data = queue->head->data;
	queue->head = queue->head->next;
	if (queue->size == 0) {
		queue->tail = NULL;
	}
	return 0;
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

