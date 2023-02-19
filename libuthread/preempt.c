#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

//#define _XOPEN_SOURCE 700

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

struct sigaction sa,normalsa;
struct itimerval old, new;
sigset_t ss;

void signal_handler(int signum) {
	if(signum == SIGVTALRM){
		//printf("I am in handler\n");
		uthread_yield();
	}
	else{
		//printf("i am in but not really\n");
		//Error handler needed
	}
}

void preempt_disable(void)
{
	//sigset_t ss;
	sigemptyset(&ss);
	sigaddset(&ss,SIGVTALRM);
	sigprocmask(SIG_BLOCK, &ss, NULL);
}

void preempt_enable(void)
{
	//Add or not?
	//sigset_t ss;
	sigemptyset(&ss);
	sigaddset(&ss,SIGVTALRM);
	sigprocmask(SIG_UNBLOCK, &ss, NULL);
}

void preempt_start(bool preempt)
{
	if (!preempt) {
		return;
	}
	else{
		sa.sa_handler = &signal_handler;
		sigemptyset(&sa.sa_mask);
		//sigaddset(&sa.sa_mask, SIGVTALRM);
		sa.sa_flags = 0;
		sigaction(SIGVTALRM,&sa,&normalsa);


		new.it_interval.tv_usec = 10000;
		new.it_interval.tv_sec = 0;
		new.it_value.tv_usec = 10000;
		new.it_value.tv_sec = 0;
	
		setitimer(ITIMER_VIRTUAL, &new, NULL);
		//printf("timer set\n");
		/*
		printf("temp value is: %d\n",temp);
		if (temp < 0) {
			perror("setitimer fail");
			exit(1);
		}
		*/
	}
}

void preempt_stop(void)
{
	//preempt_disable();

	sigaction(SIGVTALRM, &normalsa, NULL);


	new.it_interval.tv_usec = 0;
	new.it_interval.tv_sec = 0;
	new.it_value.tv_usec = 0;
	new.it_value.tv_sec = 0;
	int temp = setitimer(ITIMER_VIRTUAL, &new, &old);
	if (temp < 0) {
		perror("setitimer fail");
		exit(1);
	}
}

