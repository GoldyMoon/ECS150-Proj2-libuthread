#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <uthread.h>
#include <private.h>
#include <sem.h>
#include <time.h>

#include <unistd.h>

void thread2(void *arg)
{
	(void)arg;
	int i = 0;
	printf("should see me here\n");
	while(1){
		i++;
	}
	printf("i is now %d\n",i);
}

void thread1(void *arg)
{
	(void)arg;
  	printf("thread1 entered\n");
	uthread_create(thread2, NULL);
  	printf("thread1 continue\n");
	uthread_yield();
	printf("thread1 reenterd\n");
}

int main(void)
{
	uthread_run(true, thread1, NULL);
  //printf("main thread\n");
	return 0;
}
