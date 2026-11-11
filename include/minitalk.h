/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:42:42 by svaladar          #+#    #+#             */
/*   Updated: 2026/01/05 00:16:41 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft.h"

# define PID_ERROR "Error: Invalid PID\n"
# define PID_NOTEXIST "Process doesn't exist\n"
# define SERVER_RECEIVE "Server confirmation received.\n"
# define SERVER_WAITING "Waiting for messages...\n"
# define CLIENT_ERROR "Usage: ./client [server_pid] [message]\n"
# define SIGUSR1_ERROR "Error sending SIGUSR1\n"
# define SIGUSR2_ERROR "Error sending SIGUSR2\n"

typedef struct s_server
{
	int		client_pid;
	int		bits_received;
	char	current_byte;
}	t_server;

typedef struct s_client
{
	int				server_pid;
	unsigned char	*message;
	int				bit_position;
	int				char_index;
	int				finished;
}	t_client;

void	receive_bit(int signum, siginfo_t *info, int end_signal);
void	start_server(void (*handler)(int, siginfo_t *, void *));

int		validate_arguments(int ac, char **av);
void	send_bit_to_server(void);
void	start_client(int ac, char **av, void (*handler)(int));

#endif
