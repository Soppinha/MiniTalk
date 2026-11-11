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

static void	handle_server_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	receive_bit(signum, info, SIGUSR1);
}

int	main(void)
{
	start_server(handle_server_signal);
	return (0);
}
