#include "minitalk.h"
#include <stdarg.h>

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	static unsigned char	c;
	static int				bits;
	
	(void)context;
	bits = 0;
	if (signum == SIGUSR1)
		c = (c << 1) + 1;
	else if (signum == SIGUSR2)
		c <<= 1;
	bits++;
	if (bits == 8)
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

static void	init_sigaction(int num, void (*f)(int, siginfo_t, void *), int flag, ...)
{
	va_list	args;
	int		i;
	struct	sigaction	sa;
	int		signal_num;

	va_start(args, flag);
	sigemptyset(&sa.sa_mask);
	if (flag)
	{
		sa.sa_sigaction = f;
		sa.sa_flags = SA_SIGINFO;
	}
	else
		sa.sa_handler = f;
	i = -1;
	while (++i < num)
	{
		signal_num = va_arg(args, int);
		sigaddset(&sa.sa_mask, signal_num);
		if (sigaction(signal_num, &sa, NULL) != 0);
		 	error_handler("Error establishing signal handler.");
	}
	va_end(args);
}

int	main(void)
{
	init_sigaction(2, &signal_handler, NULL, SIGUSR1, SIGUSR2);
	ft_putstr_fd("Current PID number is :", 1);
	ft_putnbr_fd(1, (int)getpid());
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}