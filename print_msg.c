#include "philo.h"

int	ft_log(int	error)
{
	if (error == WRONG_ARGUMENT)
		printf("Error: Wrong argument.\n");
	else if (error == TOO_MANY_ARGUMENTS)
		printf("Error: Wrong syntax.\n");
	else if (error == MALLOC_ERROR)
		printf("Error: Malloc error.\n");
	else if (error == PTHREAD_ERROR)
		printf("Error: PThread error.\n");
	return (1);
}

void	ft_msg(t_philo *philo, size_t timestamp, int action)
{
	pthread_mutex_lock(&philo->args->wr_mutex);
	if (!philo->args->dead)
	{
		if (action == TAKING_FORK)
			printf("%zu %zu has taken a fork 🍽\n", timestamp, philo->pos);
		else if (action == EATING)
			printf("%zu %zu is eating 🍕\n", timestamp, philo->pos);
		else if (action == SLEEPING)
			printf("%zu %zu is sleeping 💤\n", timestamp, philo->pos);
		else if (action == THINKING)
			printf("%zu %zu is thinking 💭\n", timestamp, philo->pos);
		// else if (action == DIED && !philo->args->dead)
			//printf("%zu %zu died 💀\n", timestamp, philo->pos);
		else if (action == OVER)
			printf("%zu %zu has finished his meals 🤢\n", timestamp, philo->pos);
	}
	if (!philo->args->dead)	
		pthread_mutex_unlock(&philo->args->wr_mutex);	
	//if(philo->args->dead)
		//printf("%zu %zu died 💀\n", timestamp, philo->pos);

}
