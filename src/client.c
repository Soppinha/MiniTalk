/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/01/04 00:56:49 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_client	g_client;

void	init_client(int ac, char **av)
{
	g_client.server_pid = parse_validation(ac, av);
	g_client.msg = (unsigned char *)av[2];
	g_client.bit = 7;
	g_client.c = 0;
}

void	send_bit(void)
{
	unsigned char	mask;
	unsigned char	bit;

	if (g_client.msg[g_client.c])
	{
		mask = 1 << g_client.bit;
		bit = (g_client.msg[g_client.c] & mask) >> g_client.bit;
		if (bit == 0)
			kill(g_client.server_pid, SIGUSR1);
		else
			kill(g_client.server_pid, SIGUSR2);
		g_client.bit--;
		if (g_client.bit < 0)
		{
			g_client.bit = 7;
			g_client.c++;
		}
	}
	else
		kill(g_client.server_pid, SIGUSR1);
}

void	signal_handler_client(int signum)
{
	if (signum == SIGUSR1)
		send_bit();
	if (signum == SIGUSR2)
	{
		ft_printf("%s", SERVER_RECEIVE);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = signal_handler_client;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd(SIGUSR1_ERROR, STDERR_FILENO);
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd(SIGUSR2_ERROR, STDERR_FILENO);
		exit(1);
	}
	init_client(ac, av);
	send_bit();
	while (1)
		pause();
	return (0);
}
