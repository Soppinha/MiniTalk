/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:46:37 by svaladar          #+#    #+#             */
/*   Updated: 2025/12/23 17:27:41 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_server	g_server;

void	server_init(void)
{
	g_server.client_pid = 0;
	g_server.bit_count = 0;
	g_server.byte = 0;
}

void	write_byte(char bit)
{
	g_server.byte = (g_server.byte << 1) | bit;
	g_server.bit_count++;
	if (g_server.bit_count == 8)
	{
		if (!g_server.byte)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			kill(g_server.client_pid, SIGUSR2);
			server_init();
			return ;
		}
		else
			ft_putchar_fd(g_server.byte, STDOUT_FILENO);
		g_server.bit_count = 0;
		g_server.byte = 0;
	}
	kill(g_server.client_pid, SIGUSR1);
}

void	signal_handler_server(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_server.client_pid == 0)
		g_server.client_pid = info->si_pid;
	if (signum == SIGUSR1)
		write_byte(0);
	if (signum == SIGUSR2)
		write_byte(1);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler_server;
	server_init();
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
