/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:42:42 by svaladar          #+#    #+#             */
/*   Updated: 2026/01/05 00:16:41 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static t_server	g_server;

static void	reset_server(int client_pid)
{
	g_server.client_pid = client_pid;
	g_server.bits_received = 0;
	g_server.current_byte = 0;
}

void	receive_bit(int signum, siginfo_t *info, int end_signal)
{
	if (info->si_pid != g_server.client_pid)
	{
		if (g_server.client_pid != 0)
			write(STDOUT_FILENO, "\n", 1);
		reset_server(info->si_pid);
	}
	g_server.current_byte = (g_server.current_byte << 1)
		| (signum == SIGUSR2);
	g_server.bits_received++;
	if (g_server.bits_received < 8)
	{
		kill(g_server.client_pid, SIGUSR1);
		return ;
	}
	if (g_server.current_byte == '\0')
	{
		write(STDOUT_FILENO, "\n", 1);
		kill(g_server.client_pid, end_signal);
		reset_server(0);
		return ;
	}
	write(STDOUT_FILENO, &g_server.current_byte, 1);
	reset_server(g_server.client_pid);
	kill(g_server.client_pid, SIGUSR1);
}

void	start_server(void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	reset_server(0);
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
}
