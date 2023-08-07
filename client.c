#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	(void)argc;
	size_t	i;

	i = 0;
	while (argv[2][i])
	{
		if (argv[2][i] == '0')
			kill(atoi(argv[1]), SIGUSR1);
		else
			kill(atoi(argv[1]), SIGUSR2);
		usleep(50);
		i++;
	}
	return (0);
}
