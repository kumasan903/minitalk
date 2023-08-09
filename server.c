/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:59:21 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/10 00:26:28 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_received_signal = -1;

void	zero(int sig, siginfo_t *info, void *ctx)
{
	(void)sig;
	(void)info;
	(void)ctx;
	g_received_signal = 0;
}

void	one(int sig, siginfo_t *info, void *ctx)
{
	(void)sig;
	(void)info;
	(void)ctx;
	g_received_signal = 1;
}

void	main_loop(void)
{
	size_t			count;
	unsigned char	c;

	count = 0;
	while (1)
	{
		if (g_received_signal != -1)
		{
			if (g_received_signal == 1)
				c = c | (0b10000000 >> count);
			count++;
			g_received_signal = -1;
		}
		if (count == 8)
		{
			if (c == '\0')
				c = '\n';
			write(1, &c, 1);
			count = 0;
			c = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	sa_zero;
	struct sigaction	sa_one;

	ft_printf("%u\n", getpid());
	ft_memset(&sa_one, 0, sizeof(sa_one));
	ft_memset(&sa_zero, 0, sizeof(sa_zero));
	sa_zero.sa_sigaction = zero;
	sa_zero.sa_flags = SA_SIGINFO;
	sa_one.sa_sigaction = one;
	sa_one.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa_zero, NULL);
	sigaction(SIGUSR2, &sa_one, NULL);
	main_loop();
	return (0);
}
