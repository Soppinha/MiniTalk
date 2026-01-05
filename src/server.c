/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:46:37 by svaladar          #+#    #+#             */
/*   Updated: 2026/01/04 22:33:19 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_server	g_server;

void	init_server_state(void)
{
	g_server.client_pid = 0;
	g_server.bits_received = 0;
	g_server.current_byte = 0;
}

void	process_byte(char bit)
{
	g_server.current_byte = (g_server.current_byte << 1) | bit;
	g_server.bits_received++;
	if (g_server.bits_received == 8)
	{
		if (!g_server.current_byte)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			kill(g_server.client_pid, SIGUSR2);
			init_server_state();
			return ;
		}
		else
			ft_putchar_fd(g_server.current_byte, STDOUT_FILENO);
		g_server.bits_received = 0;
		g_server.current_byte = 0;
	}
	kill(g_server.client_pid, SIGUSR1);
}

void	handle_server_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_server.client_pid == 0)
		g_server.client_pid = info->si_pid;
	if (signum == SIGUSR1)
		process_byte(0);
	if (signum == SIGUSR2)
		process_byte(1);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_server_signal;
	init_server_state();
	ft_printf("Server PID: %d\n", getpid());
	ft_printf("%s", SERVER_WAITING);
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
	while (1)
		pause();
	return (0);
}
