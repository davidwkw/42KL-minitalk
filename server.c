/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:11:51 by kwang             #+#    #+#             */
/*   Updated: 2021/08/11 18:11:53 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdarg.h>

#define GREEN "\033[92m"
#define BOLD "\033[1m"
#define WHITE "\033[97m"
#define CYAN "\033[96m"

static void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	static unsigned char	c = 0;
	static int				bits = 0;
	static pid_t			pid = 0;

	(void)context;
	if (pid != siginfo->si_pid)
	{
		c = 0;
		bits = 0;
		pid = siginfo->si_pid;
	}
	c = (c << 1) + (signum == SIGUSR1);
	if (++bits == 8)
	{
		if (c == 4)
		{
			write(1, "\n", 1);
			kill(siginfo->si_pid, SIGUSR1);
		}
		else
			write(1, &c, 1);
		bits = 0;
		c = 0;
	}
}

static void	init_sigaction(int num, ...)
{
	va_list				args;
	int					i;
	struct sigaction	sa;
	int					signum;

	va_start(args, num);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	i = -1;
	while (++i < num)
	{
		signum = va_arg(args, int);
		sigaddset(&sa.sa_mask, signum);
		if (sigaction(signum, &sa, NULL) != 0)
			error_handler("Error establishing signal handler.");
	}
	va_end(args);
}

int	main(void)
{
	init_sigaction(2, SIGUSR1, SIGUSR2);
	ft_putstr_fd(BOLD GREEN "Server PID number is : " CYAN, 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n" BOLD WHITE, 1);
	while (1)
		pause();
	return (0);
}
