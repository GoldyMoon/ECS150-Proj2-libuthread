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

queue_t readyqueue;
struct uthread_tcb *current_thread;
struct uthread_tcb *main_thread;
struct uthread_tcb *next;

struct uthread_tcb {
	void *sp;	//  stack pointer
	int state;	//  running(0), ready(1) ,block(2), or exited(3)
	uthread_ctx_t *context;//  set of registers
};

struct uthread_tcb *uthread_current(void)
{
	return current_thread;
}

void uthread_yield(void)
{
	queue_enqueue(readyqueue, current_thread);
	struct uthread_tcb *prev;
	queue_dequeue(readyqueue, (void**)&next);
	prev = current_thread;
	current_thread = next;
	current_thread->state = 0;
	uthread_ctx_switch(prev->context,next->context);
}

void uthread_exit(void)
{	
	struct uthread_tcb *prev;
	queue_dequeue(readyqueue, (void**)&next);
	prev = current_thread;
	current_thread = next;
	current_thread->state = 0;
	uthread_ctx_destroy_stack(prev->sp);
	prev -> state = 0;
	free(prev->context);
	free(prev);
	uthread_ctx_switch(prev->context,next->context);
}

int uthread_create(uthread_func_t func, void *arg)
{
	struct uthread_tcb *temp_tcb = malloc(sizeof(struct uthread_tcb));
	uthread_ctx_t *new_context = malloc(sizeof(uthread_ctx_t));
	void* sp = uthread_ctx_alloc_stack();
	
	preempt_disable();
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
	preempt_enable();
	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	readyqueue = queue_create();
	if (preempt) {
		preempt_start(preempt);
	}
	//  main thread initialization
	main_thread = (struct uthread_tcb*)malloc(sizeof(struct uthread_tcb));
	main_thread->context = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));
	main_thread->sp = uthread_ctx_alloc_stack();
	if (main_thread == NULL || main_thread->context == NULL) {
		return -1;
	}
	current_thread = main_thread;

	if (uthread_create(func, arg)) {	//Should be in the crearte function to block sig?
		return -1;
	}
	
	while(1) {
		if(!queue_length(readyqueue)) {
			break;
		}
		//printf("back to main now\n");
		uthread_yield();
	}

  uthread_ctx_destroy_stack(current_thread->sp);
	current_thread -> state = 0;
  free(current_thread->context);
  free(current_thread);
	
	queue_destroy(readyqueue);
	preempt_stop();
	return 0;
}

//
void uthread_block(void)
{
	//struct uthread_tcb *temp = uthread_current();
	current_thread->state = 2;	//block state
	struct uthread_tcb *prev;
	struct uthread_tcb *next;
	queue_dequeue(readyqueue, (void**)&next); // 
	prev = current_thread;
	current_thread = next;
	uthread_ctx_switch(prev -> context,next -> context);
	//switch between the fisrt available and the current block thread and put the prev thread(blocked) into the waiting queue in sem.c
}

//
void uthread_unblock(struct uthread_tcb *uthread)
{
	//
	uthread->state = 1; //ready state
	queue_enqueue(readyqueue,uthread); //Put the unblocked thread into the ready queue
}