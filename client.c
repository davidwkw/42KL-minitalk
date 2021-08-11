#include "minitalk.h"

static void	success_handler(int signum)
{
	char	*success;

	success = "Message successfully printed\n";
	if (signum == SIGUSR1)
	{
		write(1, success, ft_strlen(success));
		exit(0);
	}
}

static void	dispatch_handler(pid_t pid, unsigned char c)
{
	int	status;
	int	bits;

	bits = 7;
	while (bits >= 0)
	{
		if (c & (1 << bits--))
			status = kill(pid, SIGUSR1);
		else
			status = kill(pid, SIGUSR2);
		if (status != 0)
			error_handler("A signal was not sent\n");
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		error_handler("Invalid input. Try ./client [PID] [message]\n");
	signal(SIGUSR1, success_handler);
	pid = (pid_t)ft_atoi(argv[1]);
	while (*argv[2])
		dispatch_handler(pid, *argv[2]++);
	dispatch_handler(pid, 4);
	usleep(50);
	return (0);
}