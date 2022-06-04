#include "philo.h"

int even_philos_taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
	ft_msg(philo, TAKING_FORK);
	philo->args->forks[philo->l_frk] = 1;
	if (philo->args->num_philo > 1)
	{
		pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
		ft_msg(philo, TAKING_FORK);
		philo->args->forks[philo->r_frk] = 1;
	}
	else
	{
		while (!philo->args->dead)
		{
			if (philo->args->dead)
				break ;
		}
		return (1);
	}
	return (0);
}

void odd_philos_taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
	ft_msg(philo, TAKING_FORK);
	philo->args->forks[philo->r_frk] = 1;
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
	ft_msg(philo, TAKING_FORK);
	philo->args->forks[philo->l_frk] = 1;
}

int	take_forks(t_philo *philo)
{
	if (philo->pos % 2 == 0)
	{
		if (even_philos_taking_fork(philo))
			return (1);
	}
	else
		odd_philos_taking_fork(philo);
	return (0);
}

int	eat(t_philo *philo)
{
	philo->eating = 1;
	philo->lst_meal = get_time();
	//printf("\n philo %ld lst meal time = %lld\n", philo->pos,philo->lst_meal);
	ft_msg(philo, EATING);
	ft_usleep(philo->args->eat_time);
	philo->lst_meal = get_time();
	philo->eating = 0;
	philo->num_of_meals += 1;
	if (philo->args->num_to_eat > 0 && (long long int)philo->num_of_meals >= philo->args->num_to_eat)
	{
		ft_msg(philo,  OVER);
		philo->args->forks[philo->l_frk] = 0;
		pthread_mutex_unlock(&philo->args->forks_mutexes[philo->l_frk]);
		philo->args->forks[philo->r_frk] = 0;
		pthread_mutex_unlock(&philo->args->forks_mutexes[philo->r_frk]);
		philo->args->finished++;
		return (1);
	}
	return (0);
}

int	release_forks(t_philo *philo)
{
	philo->args->forks[philo->l_frk] = 0;
	pthread_mutex_unlock(&philo->args->forks_mutexes[philo->l_frk]);
	philo->args->forks[philo->r_frk] = 0;
	pthread_mutex_unlock(&philo->args->forks_mutexes[philo->r_frk]);
	ft_msg(philo, SLEEPING);
	ft_usleep(philo->args->sleep_time);
	ft_msg(philo,THINKING);
	return (0);
}

void	*routine(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	while (!philo->args->dead)
	{
		if (take_forks(philo) || eat(philo) || release_forks(philo))
			break ;
	}
	return (NULL);
}
