#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"

struct uthread_tcb {
	void *sp;	//  stack pointer
	int state;	//  running(0), ready(1) ,block(2), unblock(3), or exited(4)
	uthread_ctx_t *context;//  set of registers
};

queue_t readyqueue;
struct uthread_tcb *current_thread;
//struct uthread_tcb *next_thread;
//struct uthread_tcb main_thread;

struct uthread_tcb *uthread_current(void)
{
	return current_thread;
}

void uthread_yield(void)
{
	/*
	current_thread = uthread_current();
  queue_enqueue(readyqueue, current_thread); 
  struct uthread_tcb *prev_thread;
  struct uthread_tcb *next_thread;
  queue_dequeue(readyqueue, (void**)&next_thread); 
  prev_thread = current_thread;
  current_thread = next_thread;
  uthread_ctx_switch(prev_thread->context, next_thread->context);
	*/

	
	current_thread = uthread_current();
	queue_enqueue(readyqueue, current_thread);
	struct uthread_tcb *next = malloc(sizeof(struct uthread_tcb));
	struct uthread_tcb *prev = malloc(sizeof(struct uthread_tcb));
	queue_dequeue(readyqueue, (void**)&next);
	prev = current_thread;
	current_thread = next;
	current_thread->state = 0;
	uthread_ctx_switch(prev->context,next->context);
}

void uthread_exit(void)
{	
	struct uthread_tcb *temp = uthread_current();
	struct uthread_tcb *next = malloc(sizeof(struct uthread_tcb));
	queue_dequeue(readyqueue, (void**)&next);
	temp->state = 4;
	uthread_ctx_switch(temp->context,next->context);
	uthread_ctx_destroy_stack(temp->sp);
	free(temp);
}

int uthread_create(uthread_func_t func, void *arg)
{
	struct uthread_tcb *temp_tcb = malloc(sizeof(struct uthread_tcb));
	uthread_ctx_t *new_context = malloc(sizeof(uthread_ctx_t));
	void* sp = uthread_ctx_alloc_stack();
	if (temp_tcb == NULL || new_context == NULL || sp == NULL) {
		return -1;
	}
	temp_tcb->state = 1;
	temp_tcb->sp = sp;
	temp_tcb->context = new_context;
	if (uthread_ctx_init(new_context,sp,func,arg)) {
		return -1;
	}
	queue_enqueue(readyqueue, temp_tcb);
	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{


	readyqueue = queue_create();
	if (preempt) {
		printf("testing: preemptive scheduling is enabled.\n");
	}
	//  main thread initialization?
	struct uthread_tcb* main_thread = (struct uthread_tcb*)malloc(sizeof(struct uthread_tcb));
	main_thread->context = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));
	main_thread->sp = uthread_ctx_alloc_stack();
	if (main_thread == NULL || main_thread->context == NULL) {
		return -1;
	}
	current_thread = main_thread;

	if (uthread_create(func, arg)) {
		return -1;
	}

	while(1) {
		if(!queue_length(readyqueue)) {
			break;
		}
		uthread_yield();
	}
	queue_destroy(readyqueue);
	return 0;
}

void uthread_block(void)
{
	struct uthread_tcb *temp = uthread_current();
	temp->state = 2;
	// switch??
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	uthread->state = 3;
}
