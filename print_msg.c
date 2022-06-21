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

void	ft_msg(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->args->wr_mutex);
	if (philo->args->dead)
	{
		pthread_mutex_unlock(&philo->args->wr_mutex);
		return ;
	}
	if (action == TAKING_FORK)
		printf("%lld - philo %ld has taken a fork 🍽\n", philo->args->time - get_time(), philo->pos);
	else if (action == EATING)
		printf("%lld - philo %ld is eating 🍕\n", philo->args->time - get_time() , philo->pos);
	else if (action == SLEEPING)
		printf("%lld - philo %ld is sleeping 💤\n", philo->args->time - get_time(), philo->pos);
	else if (action == THINKING)
		printf("%lld - philo %ld is thinking 💭\n", philo->args->time - get_time(), philo->pos);
	else if (action == OVER)
		printf("%lld - philo %ld has finished his meals 🤢\n", philo->args->time - get_time(), philo->pos);
	else if (action == DIED)
	{
		pthread_mutex_lock(&philo->args->die_mutex);
		philo->args->dead = 1;
		pthread_mutex_unlock(&philo->args->die_mutex);
		printf("%lld - philo %ld died 💀\n",philo->args->time - get_time(),philo->pos);
		return ;
	}
	pthread_mutex_unlock(&philo->args->wr_mutex);
}
