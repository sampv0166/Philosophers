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
	{
		//pthread_mutex_lock(&philo->args->wr_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->args->wr_mutex);
	if (action == TAKING_FORK)
		printf("%zu - philo %zu has taken a fork 🍽\n", timestamp, philo->pos);
	else if (action == EATING)
		printf("%zu - philo %zu is eating 🍕\n", timestamp, philo->pos);
	else if (action == SLEEPING)
		printf("%zu - philo %zu is sleeping 💤\n", timestamp, philo->pos);
	else if (action == THINKING)
		printf("%zu - philo %zu is thinking 💭\n", timestamp, philo->pos);
	else if (action == OVER)
		printf("%zu - philo %zu has finished his meals 🤢\n", timestamp, philo->pos);
	if (action == DIED)
	{
		printf("%zu - philo %zu dieds 💀\n", get_time() - philo->lst_meal, philo->pos);
		philo->args->dead = 1;
	}
	pthread_mutex_unlock(&philo->args->wr_mutex);
}
