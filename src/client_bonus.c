/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:42:42 by svaladar          #+#    #+#             */
/*   Updated: 2026/01/05 00:16:41 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	handle_client_signal(int signum)
{
	if (signum == SIGUSR1)
		send_bit_to_server();
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd(SERVER_RECEIVE, STDOUT_FILENO);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	start_client(ac, av, handle_client_signal);
	return (0);
}
