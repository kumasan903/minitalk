/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:22:29 by skawanis          #+#    #+#             */
/*   Updated: 2023/10/08 18:44:07 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	action(int signal)
{
	static char		c;
	static size_t	count;

	if (signal == SIGUSR2)
		c = c | (0b10000000 >> count);
	count++;
	if (count == 8)
	{
		if (c == '\0')
			c = '\n';
		write(1, &c, 1);
		count = 0;
		c = 0;
	}
}

int	main(void)
{
	ft_printf("%u\n", getpid());
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	while (1)
		pause();
}
