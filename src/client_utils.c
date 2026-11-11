/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:39:47 by svaladar          #+#    #+#             */
/*   Updated: 2026/01/04 22:57:51 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static t_client	g_client;

static int	is_valid_pid(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_arguments(int ac, char **av)
{
	int	server_pid;

	if (ac != 3 || av[1][0] == '\0' || av[2][0] == '\0')
	{
		ft_putstr_fd(CLIENT_ERROR, STDERR_FILENO);
		exit(1);
	}
	if (!is_valid_pid(av[1]))
	{
		ft_putstr_fd(PID_ERROR, STDERR_FILENO);
		exit(1);
	}
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0)
	{
		ft_putstr_fd(PID_ERROR, STDERR_FILENO);
		exit(1);
	}
	if (kill(server_pid, 0) == -1)
	{
		ft_putstr_fd(PID_NOTEXIST, STDERR_FILENO);
		exit(1);
	}
	return (server_pid);
}

void	send_bit_to_server(void)
{
	unsigned char	c;

	if (g_client.finished)
		exit(0);
	c = g_client.message[g_client.char_index];
	if ((c >> g_client.bit_position) & 1)
		kill(g_client.server_pid, SIGUSR2);
	else
		kill(g_client.server_pid, SIGUSR1);
	g_client.bit_position--;
	if (g_client.bit_position < 0)
	{
		if (c == '\0')
			g_client.finished = 1;
		g_client.bit_position = 7;
		g_client.char_index++;
	}
}

void	start_client(int ac, char **av, void (*handler)(int))
{
	struct sigaction	sa;

	g_client.server_pid = validate_arguments(ac, av);
	g_client.message = (unsigned char *)av[2];
	g_client.bit_position = 7;
	g_client.char_index = 0;
	g_client.finished = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd(SIGUSR1_ERROR, STDERR_FILENO);
		exit(1);
	}
	send_bit_to_server();
	while (1)
		pause();
}
