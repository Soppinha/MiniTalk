/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:42:42 by svaladar          #+#    #+#             */
/*   Updated: 2026/01/04 22:39:44 by sofiab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "../libft/libft.h"

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
}	t_client;


void	init_server_state(void);
void	process_byte(char bit);
void	handle_server_signal(int signum, siginfo_t *info, void *context);


void	init_client_state(int ac, char **av);
void	send_bit_to_server(void);
void	handle_client_signal(int signum);
int		validate_arguments(int ac, char **av);

#endif