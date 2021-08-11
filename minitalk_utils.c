#include "minitalk.h"

void	error_handler(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}