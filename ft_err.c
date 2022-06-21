#include "philo.h"

int	ft_err(int	error)
{
	if (error == NOT_ENOUGH_ARGUMENTS)
		printf("Error: Not Enough argumens.\n");
	else if (error == WRONG_ARGUMENT)
		printf("Error: Wrong argument.\n");
	else if (error == TOO_MANY_ARGUMENTS)
		printf("Error: Wrong syntax.\n");
	else if (error == MALLOC_ERROR)
		printf("Error: Malloc error.\n");
	else if (error == PTHREAD_ERROR)
		printf("Error: PThread error.\n");
	return (1);
}
