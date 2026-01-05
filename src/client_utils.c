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
