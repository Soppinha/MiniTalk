/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:42:42 by svaladar          #+#    #+#             */
/*   Updated: 2026/01/05 00:16:41 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	handle_server_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	receive_bit(signum, info, SIGUSR2);
}

int	main(void)
{
	start_server(handle_server_signal);
	return (0);
}
