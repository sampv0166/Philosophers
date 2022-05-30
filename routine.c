#include "philo.h"

int	is_dead(t_philo *philo)
{
	if ((!philo->eating && get_time() > philo->max_time))
	{
		ft_msg(philo, philo->max_time, DIED);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
		if (philo->args->forks[philo->l_frk] == 0)
		{
			if (is_dead(philo))
				return (1);
			ft_msg(philo, get_time(), TAKING_FORK);
			philo->args->forks[philo->l_frk] = 1;
		}
		if (philo->args->num_philo > 1)
		{
			if (is_dead(philo))
				return (1);
			pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
			if (philo->args->forks[philo->r_frk] == 0)
			{
				ft_msg(philo, get_time(), TAKING_FORK);
				philo->args->forks[philo->r_frk] = 1;
			}
		}
		else
		{
			ft_usleep(philo->args->death_time);
			ft_msg(philo, philo->max_time, DIED);
			return (1);
		}
	}
	else 
	{
		pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
		if (philo->args->forks[philo->r_frk] == 0)
		{
			if (is_dead(philo))
				return (1);
			ft_msg(philo, get_time(), TAKING_FORK);
			philo->args->forks[philo->r_frk] = 1;
		}
		pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
		if (philo->args->forks[philo->l_frk] == 0)
		{
			if (is_dead(philo))
				return (1);
			ft_msg(philo, get_time(), TAKING_FORK);
			philo->args->forks[philo->l_frk] = 1;
		}
	}
	return (0);
}

int	eat(t_philo *philo)
{
	philo->eating = 1;
	philo->lst_meal = get_time();
	ft_msg(philo, philo->lst_meal, EATING);
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
	ft_msg(philo, philo->lst_meal + philo->args->eat_time, SLEEPING);
	ft_usleep(philo->args->sleep_time);
	if (is_dead(philo))
		return (1);
	ft_msg(philo, philo->lst_meal + philo->args->eat_time
		+ philo->args->sleep_time, THINKING);
	return (0);
}

void	*routine(void *philo_t)
{
	t_philo	*philo;
	philo = (t_philo *)philo_t;
	philo->lst_meal = get_time();
	philo->max_time = philo->lst_meal + philo->args->death_time;
	while (1)
	{
		if (take_forks(philo) || eat(philo) || release_forks(philo))
		{
			break ;
		}
	}
	return (NULL);
}
