#include "philo.h"

int	is_dead(t_philo *philo)
{
	if ((get_time() - philo->lst_meal >  philo->args->death_time))
	{
		ft_msg(philo, get_time() - philo->lst_meal, DIED);	
		philo->args->dead = 1;
		return (1);
	}
	return (0);
}

int even_philos_taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
	if (is_dead(philo))
		return (1);
	ft_msg(philo, get_time() - philo->lst_meal, TAKING_FORK);
	philo->args->forks[philo->l_frk] = 1;
	if (philo->args->num_philo > 1)
	{
		pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
		ft_msg(philo, get_time() - philo->lst_meal, TAKING_FORK);
		philo->args->forks[philo->r_frk] = 1;
	}
	else
	{
		while (!philo->args->dead)
		{
			if (is_dead(philo))
				break ;
		}
		return (1);
	}
	return (0);
}

void odd_philos_taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
	if (is_dead(philo))
		return ;	
	ft_msg(philo, get_time() - philo->lst_meal, TAKING_FORK);
	philo->args->forks[philo->r_frk] = 1;
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
	ft_msg(philo, get_time() - philo->lst_meal, TAKING_FORK);
	philo->args->forks[philo->l_frk] = 1;
}

int	take_forks(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
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
	// if (!philo->args->dead)
	ft_msg(philo,get_time() -  philo->lst_meal, EATING);
	ft_usleep(philo->args->eat_time);
	philo->max_time = philo->lst_meal + philo->args->death_time;
	philo->eating = 0;
	philo->num_of_meals += 1;
	if (philo->args->num_to_eat > 0 && philo->num_of_meals >= philo->args->num_to_eat)
	{
		ft_msg(philo, philo->lst_meal , OVER);
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
	ft_msg(philo, get_time() -  philo->lst_meal, SLEEPING);
	ft_usleep(philo->args->sleep_time);
	ft_msg(philo, get_time() - philo->lst_meal, THINKING);

	// if (is_dead(philo))
	// 	return (1);
	return (0);
}

void	*routine(void *philo_t)
{
	// size_t i;
	// i = 0;

	t_philo	*philo;
	philo = (t_philo *)philo_t;
	philo->lst_meal = get_time();
	//philo->max_time = philo->lst_meal + philo->args->death_time;
	while (!philo->args->dead)
	{
		if (take_forks(philo) || eat(philo) || release_forks(philo))
			break;
	}
	return (NULL);
}
