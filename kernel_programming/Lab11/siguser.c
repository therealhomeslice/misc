#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void sigcatch(int sig)
{
	printf("Waking up! Caught signal: %d\n", sig);
}

int main(void)
{
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = sigcatch;

	sigaction(SIGABRT, &act, 0);
	sigaction(SIGTRAP, &act, 0);
	sigaction(SIGQUIT, &act, 0);

	while(1)
	{
		printf("sleeping .. ZZZzzz ...\n");
		sleep(1);
	}
}
