#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200809L

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_server
{
	unsigned char	current_char;
	int				bit_count;
	int				client_pid;
}	t_server;

void	ft_putchar(char c);
void	ft_putnbr(int n);
void	ft_putstr(char *str);
int		ft_atoi(char *str);
int		is_valid_pid(char *str);

#endif