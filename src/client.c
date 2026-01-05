/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/01/04 22:34:02 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_client	g_client;

void	init_client_state(int ac, char **av)
{
	g_client.server_pid = validate_arguments(ac, av);
	g_client.message = (unsigned char *)av[2];
	g_client.bit_position = 7;
	g_client.char_index = 0;
}

void	send_bit_to_server(void)
{
	unsigned char	mask;
	unsigned char	bit;

	if (g_client.message[g_client.char_index])
	{
		mask = 1 << g_client.bit_position;
		bit = (g_client.message[g_client.char_index] & mask)
			>> g_client.bit_position;
		if (bit == 0)
			kill(g_client.server_pid, SIGUSR1);
		else
			kill(g_client.server_pid, SIGUSR2);
		g_client.bit_position--;
		if (g_client.bit_position < 0)
		{
			g_client.bit_position = 7;
			g_client.char_index++;
		}
	}
	else
		kill(g_client.server_pid, SIGUSR1);
}

void	handle_client_signal(int signum)
{
	if (signum == SIGUSR1)
		send_bit_to_server();
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
	sa.sa_handler = handle_client_signal;
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
	init_client_state(ac, av);
	send_bit_to_server();
	while (1)
		pause();
	return (0);
}
