#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct queue {
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
	if (queue == NULL || queue->size != 0) {
		return -1;
	}
	free(queue);
	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	if (data == NULL || queue == NULL) {
		return -1;
	}
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
	struct node* temp = queue->head;
	if (queue == NULL || data == NULL || queue->size == 0) {
		return -1;
	}
	queue->size--;
	*data = queue->head->data;
	queue->head = queue->head->next;
	if (queue->size == 0) {
		queue->tail = NULL;
	}
	free(temp);
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	struct node* head = queue->head;
	struct node* tail = queue->tail;
	struct node* temp = head;
	struct node* match;

	if (queue == NULL || data == NULL) {
		return -1;
	}
	//  if the first element match or there's only 1 node
	if (head->data == data || queue->size == 1) {
		queue_dequeue(queue, &data);
		return 0;
	}
	//  Loop through the queue
	while (temp->data != data) {
		if (temp->next->data == data) {
			match = temp->next;
			temp->next = match->next;
			if (temp->next == tail) {
				queue->tail = temp;
			}
			free(match);
			queue->size--;
		} else {
			temp = temp->next;
		}
	}
	//  Not found
	if (temp == NULL) {
		return -1;
	}
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	struct node* temp = queue->head;
	struct node* next;
	if (queue == NULL || func == NULL) {
		return -1;
	}
	while (true) {
		next = temp->next;
		func(queue, temp->data);
		temp = next;
	}
	return 0;
}

int queue_length(queue_t queue)
{
	return queue->size;
}

