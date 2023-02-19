#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <uthread.h>
#include <private.h>
#include <sem.h>
#include <time.h>

#include <unistd.h>

int cost = 1;
int *argsh = &cost;

void thread2(void *arg)
{	
	//int i = 0;
	int *int_ptr = (int *)arg;
	printf("thread2 entered\n");
	//printf("cost is now %d\n",*int_ptr);
	//uthread_yield();
	//printf("thread2 reentered\n");
	printf("cost is now %d\n",*int_ptr);
	while(1){
		//printf("cost is now %d\n",cost);
		/*
		if(i ==40000){
			uthread_yield();
			printf("cost is now %d\n",*int_ptr);
		}
		i++;
		*/
		preempt_disable();
		if(*int_ptr == 0){
			printf("Finish all the loop, about to exit\n");
			uthread_exit();
		}
		preempt_enable();
	}
	
}

void thread1(void *arg)
{
	(void)arg;
  printf("thread1 entered\n");
	uthread_create(thread2, argsh);
  printf("thread1 continue\n");
	uthread_yield();
	preempt_disable();
	cost = 0;
	//printf("cost right after change is %d\n",cost);
	printf("thread1 reenterd\n");
	printf("cost right after change is %d\n",cost);
	preempt_enable();
	//uthread_exit();
}

int main(void)
{
	uthread_run(true, thread1, NULL);
  printf("main thread\n");
	return 0;
}

//expected output with preempt enable is:
//thread1 entered, thread1 countinue, should me see me here, thread1 reentered, finish all the loop, about tho exit, main thread