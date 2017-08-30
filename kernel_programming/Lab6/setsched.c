#include <stdio.h>
#include <unistd.h>
#include <linux/sched.h>
#include <sys/resource.h>

/*
 * Scheduling policies defined in sched.h
#define SCHED_NORMAL	0
#define SCHED_FIFO		1
#define SCHED_RR		2
#define SCHED_BATCH		3
 */

struct sched_param {
	int sched_priority;
};

struct sched_param s_param;

void setscheduler(void)
{

	/* call sched_getparam() to initialize s_param struct */
	int rv = sched_getparam( getpid(), &s_param);
	printf("RV:%i\n", rv);
	//s_param is initialized;
	//rv will be 0 is successful, -1 if not
	if (rv == 0)
	{
		/* set sched priority to 1 and schedule policy to FIFO */
		int prioritysuccess = setpriority(s_param.sched_priority, getpid(), -10);
		//s_param.sched_priority holds the priority value of the current task
		//getpid() returns the current pid of the calling process
		//1 is the new priority
		//returns 0 on success
		printf("priority:%i\n", prioritysuccess);

		int policysuccess = sched_setscheduler( getpid(), 1, &s_param);
		//1 means SCHED_FIFO
		//s_param is the initialized structure
		printf("policy:%i\n", policysuccess);
		//returns 0 for success, -1 for error
		if (policysuccess == 0)
		{
			printf("Scheduler set to SCHED_FIFO with priority %i...\n", s_param.sched_priority);
		}
		else
		{	/* check for errors */
			printf("!!!Scheduler set to SCHED_FIFO with priority %i FAILED!!!\n", s_param.sched_priority);
		}
	}
}

int main()
{
	setscheduler();

	while(1)
	{
		printf("PID %i sleeping..\n", getpid());
		switch(sched_getscheduler(getpid()))
		{
			case SCHED_NORMAL: printf("sched_getscheduler() = SCHED_NORMAL\n");
								break;
			case SCHED_FIFO: printf("sched_getscheduler() = SCHED_FIFO\n");
								break;
			case SCHED_RR: printf("sched_getscheduler() = SCHED_RR\n");
								break;
			case SCHED_BATCH: printf("sched_getscheduler() = SCHED_BATCH\n");
								break;
			default:
				break;
		}

		printf("Process priority %i...\n", getpriority(PRIO_PROCESS, 0));
		sleep(5);
	}
}
