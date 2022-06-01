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
	if (philo->args->dead)
		return ;
	pthread_mutex_lock(&philo->args->wr_mutex);
	if (action == TAKING_FORK)
		printf("%zu %zu has taken a fork 🍽\n", timestamp, philo->pos);
	else if (action == EATING)
		printf("%zu %zu is eating 🍕\n", timestamp, philo->pos);
	else if (action == SLEEPING)
		printf("%zu %zu is sleeping 💤\n", timestamp, philo->pos);
	else if (action == THINKING)
		printf("%zu %zu is thinking 💭\n", timestamp, philo->pos);
	else if (action == OVER)
		printf("%zu %zu has finished his meals 🤢\n", timestamp, philo->pos);
	if (action == DIED)
	{
		printf("%zu %zu died 💀\n", get_time(), philo->pos);
		philo->args->dead = 1;
	}
	pthread_mutex_unlock(&philo->args->wr_mutex);
}
