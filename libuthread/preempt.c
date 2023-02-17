#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

struct sigaction sa;
struct itimerval old, new;
sigset_t ss;

void signal_handler(void) {
	uthread_yield();
}

void preempt_disable(void)
{
	sigpromask(SIG_BLOCK, &ss, NULL);
}

void preempt_enable(void)
{
	sigpromask(SIG_UNBLOCK, &ss, NULL);
}

void preempt_start(bool preempt)
{
	if (!preempt) {
		return;
	}
	int micro_seconds = 100000/HZ;
	sigemptyset(&ss);
	sigaddset(&ss, SIGVTALRM);
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flag = 0;
	sigaction(SIGVTALRM, &sa, NULL);
	it_val.it_value.tv_sec = 0;
	it_val.it_value.tv.usec = 1;
	it_val.it_interval.tv_sec = 0;
	it_val.it_interval.tv_usec = micro_seconds;
	if (setitimer(ITIMER_VIRTUAL, &new, &old) < 0) {
		perror("setitimer");
		exit(1);
	}
}

void preempt_stop(void)
{
	preempt_disable();
	sigaction(SIGALRM, &sa, NULL);
}

