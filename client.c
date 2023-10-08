/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:59:15 by skawanis          #+#    #+#             */
/*   Updated: 2023/10/08 18:46:09 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
*/

#include "minitalk.h"

void	send_char(unsigned char c, pid_t pid)
{
	size_t	i;

	i = 0;
	while (i < 8)
	{
		if (c & 0b10000000)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c << 1;
		i++;
		usleep(500);
	}
}

int	main(int argc, char **argv)
{
	size_t	i;
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putendl_fd("argc != 3", 2);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		return (1);
	i = 0;
	while (argv[2][i])
	{
		send_char(argv[2][i], server_pid);
		i++;
	}
	send_char(argv[2][i], server_pid);
	return (0);
}
