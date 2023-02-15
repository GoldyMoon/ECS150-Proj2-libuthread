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
	/* TODO Phase 2 */
	void* sp;	//stack pointer
	int state;	//running, ready ,block or exited
	uthread_ctx_t context;//set of registers
};

queue_t readyqueue;
struct uthread_tcb *current_thread;
struct uthread_tcb *next_thread;
struct uthread_tcb main_thread;

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/3 */
	return current_thread;
}

void uthread_yield(void)
{
	uthread_ctx_switch(current_thread,queue_dequeue(readyqueue,next_thread));
	/* TODO Phase 2 */
}

void uthread_exit(void)
{	
	uthread_ctx_switch();
	/* TODO Phase 2 */
}

int uthread_create(uthread_func_t func, void *arg)
{
	uthread_ctx_t *uctx;
	void* sp;
	sp = uthread_ctx_alloc_stack();
	uthread_ctx_init(uctx,sp,func,arg);
	/* TODO Phase 2 */
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */

	//ready_queue = queue_create();
	current_thread = &main_thread;

	// uthread_create(func);

	while(1) {
		
		if(queue_length(readyqueue)) {
			break;
		}
		
	uthread_yield();
	}


}

void uthread_block(void)
{
	/* TODO Phase 3 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 3 */
}

