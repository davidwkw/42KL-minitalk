#include "minitalk.h"

static void	success_handler(int signum)
{
	if (signum == SIGUSR1)
		return (write(1, "Message successfully printed", 1));
}

static void	dispatch_handler(pid_t pid, char c)
{
	int	status;
	int	bits;

	bits = 8;
	while (bits >= 0)
	{
		if (c & (1 << bits))
			status = kill(pid, SIGUSR1);
		else
			status = kill(pid, SIGUSR2);
		bits--;
		if (status != 0)
			error_handler("A signal was not sent");
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		bit;

	if (argc != 3)
		error_handler("Invalid input. Try ./client [PID] [message]");
	signal(SIGUSR1, success_handler);
	pid = (pid_t)ft_atoi(argv[1]);
	while (*argv[2])
		dispatch_handler(pid, *argv[2]++);
	dispatch_handler(pid, 4);
	usleep(50);
	return (0);
}