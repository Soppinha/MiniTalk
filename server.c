#include "minitalk.h"

t_server	g_server = {0, 0, 0};

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + '0');
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	reset_server_state(void)
{
	g_server.current_char = 0;
	g_server.bit_count = 0;
}

void	send_confirmation(int client_pid)
{
	if (client_pid > 0)
	{
		if (kill(client_pid, SIGUSR2) == -1)
		{
			ft_putstr("\nError: Failed to send confirmation\n");
			reset_server_state();
		}
	}
}

void	process_complete_char(void)
{
	if (g_server.current_char == 0)
	{
		ft_putchar('\n');
		send_confirmation(g_server.client_pid);
		reset_server_state();
	}
	else
	{
		ft_putchar(g_server.current_char);
		g_server.current_char = 0;
		g_server.bit_count = 0;
	}
}

void	process_bit(int bit)
{
	g_server.current_char |= (bit << g_server.bit_count);
	g_server.bit_count++;
	if (g_server.bit_count == 8)
		process_complete_char();
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid != 0)
		g_server.client_pid = info->si_pid;
	if (sig == SIGUSR1)
		process_bit(0);
	else if (sig == SIGUSR2)
		process_bit(1);
	send_confirmation(g_server.client_pid);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr("Error: sigaction SIGUSR1 failed\n");
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("Error: sigaction SIGUSR2 failed\n");
		exit(1);
	}
}

int	main(void)
{
	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	ft_putstr("Waiting for messages...\n");
	setup_signals();
	while (1)
		pause();
	return (0);
}
