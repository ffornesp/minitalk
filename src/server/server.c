/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:51:59 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 15:50:40 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static void	bit_to_char(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i = i | (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_putchar_fd(i, 1);
		bit = 0;
		i = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	signal(SIGUSR1, bit_to_char);
	signal(SIGUSR2, bit_to_char);
	while (1)
		pause();
	return (0);
}
