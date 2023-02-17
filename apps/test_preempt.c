#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <uthread.h>
#include <private.h>

void thread2(void *arg)
{
	(void)arg;
  while(1){
    printf("still here t2\n");
  }
}

void thread1(void *arg)
{
	(void)arg;
  printf("thread1 entered\n");
	uthread_create(thread2, NULL);
  printf("thread1 entered\n");
	uthread_yield();
	printf("thread1 reenterd\n");
}

int main(void)
{
	uthread_run(false, thread1, NULL);
  printf("main thread\n");
	return 0;
}