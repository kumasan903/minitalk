#include <string.h>
#include <stddef.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t received_signal = -1;

void zero(int sig, siginfo_t *info, void *ctx)
{
	received_signal = 0;
}

void one(int sig, siginfo_t *info, void *ctx)
{
	received_signal = 1;
}

int	main(void)
{
	struct sigaction sa_zero;
	struct sigaction sa_one;

	memset(&sa_one, 0, sizeof(sa_one));
	memset(&sa_zero, 0, sizeof(sa_zero));
	sa_zero.sa_sigaction = zero;
	sa_zero.sa_flags = SA_SIGINFO;
	sa_one.sa_sigaction = one;
	sa_one.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa_zero, NULL);
	sigaction(SIGUSR2, &sa_one, NULL);
	while (1)
	{
		if (received_signal == 0)
		{
			write(1, "0", 1);
			received_signal = -1;
		}
		else if (received_signal == 1)
		{
			write(1, "1", 1);
			received_signal = -1;
		}
		sleep (1);
	}
}
