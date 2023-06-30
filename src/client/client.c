/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:51:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 15:32:24 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static int	signal_recieved(int signal)
{
	static int	received;

	ft_printf("Original value: %d\n", received);
	if (signal == SIGINT)
	{
		ft_printf("AYAYA\n");
		received = 1;
	}
	return (received);
}

static void	pid_error(void)
{
	ft_putstr_fd("Incorrect server PID\n", 2);
	exit(1);
}

static void	usleep_wrapper(int time)
{
	int	i;
	int	j;

	i = 0;
	j = time / 10;
	while (i < j)
	{
		usleep(10);
		i++;
	}
}

static int	send_bits(int server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)))
		{
			if (kill(server_pid, SIGUSR1))
				pid_error();
		}
		else if (kill(server_pid, SIGUSR2))
			pid_error();
		usleep_wrapper(300);
		bit++;
	}
	if (signal_recieved(0))
		return (0);
	return (1);
}

static int	only_digit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	int	server_pid;
	int	i;

	if (argc != 3 || !only_digit_str(argv[1]))
	{
		ft_printf("Usage: ./client 'server_pid' 'string'\n");
		return (0);
	}
	i = 0;
	signal(SIGINT, (void *)&signal_recieved);
	server_pid = ft_atoi(argv[1]);
	while (argv[2][i] != '\0')
	{
		if (!send_bits(server_pid, argv[2][i++]))
		{
			send_bits(server_pid, '\0');
			break ;
		}
	}
	return (0);
}
