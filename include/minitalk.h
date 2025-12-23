/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:42:42 by svaladar          #+#    #+#             */
/*   Updated: 2025/12/23 17:26:57 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "../libft/libft.h"

# define PID_ERROR "Error: Invalid PID\n"
# define PID_NOTEXIST "Process doesn't exist\n"
# define SERVER_ERROR " "
# define SERVER_RECEIVE "Server confirmation received.\n"
# define SERVER_WAITING "Waiting for messages...\n"
# define CLIENT_ERROR "Usage: ./client [server_pid] [message]\n"
# define SIGUSR1_ERROR "Error sending SIGUSR1\n"
# define SIGUSR2_ERROR "Error sending SIGUSR2\n"

typedef struct s_server
{
	int		client_pid;
	int		bit_count;
	char	byte;
}	t_server;

typedef struct s_client
{
	unsigned char	*msg;
	int				server_pid;
	int				bit;
	int				c;
}	t_client;

int		is_valid_pid(char *s);
int		parse_validation(int ac, char **av);

void	init_client(int ac, char **av);
void	send_bit(void);
void	signal_handler_client(int signum);

void	server_init(void);
void	write_byte(char bit);
void	signal_handler_server(int signum, siginfo_t *info, void *context);

#endif