/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:47:31 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/20 19:31:39 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int even_philos_taking_fork(t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	while (i < 2)
// 	{
// 		if (i == 0)
// 		{
// 			pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
// 			if (philo->args->forks[philo->l_frk] == 0)
// 			{
// 				ft_msg(philo, TAKING_FORK);
// 				philo->args->forks[philo->l_frk] = 1;
// 				i++;
// 			}
// 			else
// 			{
// 				continue ;
// 			}
// 		}
// 		else if (i == 1)
// 		{
// 			if (philo->args->num_philo > 1)
// 			{
// 				pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
// 				if (philo->args->forks[philo->r_frk] == 0)
// 				{
// 					ft_msg(philo, TAKING_FORK);
// 					philo->args->forks[philo->r_frk] = 1;
// 					i++;
// 				}
// 				else
// 				{
// 					continue;
// 				}	
// 			}
// 			else
// 			{
// 				while (!philo->args->dead)
// 				{
// 					if (philo->args->dead)
// 						break ;
// 				}
// 				return (1);
// 			}
// 		}
// 	}
// 	return (0);
// }

// void odd_philos_taking_fork(t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	while (i < 2)
// 	{
// 		if (i == 0)
// 		{
// 			pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
// 			if (philo->args->forks[philo->r_frk] == 0)
// 			{
// 				ft_msg(philo, TAKING_FORK);
// 				philo->args->forks[philo->r_frk] = 1;
// 				i++;
// 			}
// 			else
// 			{
// 				continue;
// 			}
// 		}
// 		else if (i == 1)
// 		{
// 			pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
// 			if (philo->args->forks[philo->l_frk] == 0)
// 			{
// 				ft_msg(philo, TAKING_FORK);
// 				philo->args->forks[philo->l_frk] = 1;
// 				i++;
// 			}
// 			else
// 			{
// 				continue;
// 			}
// 		}
// 	}
// }
//printf("\n time before taking forks =  %lld\n", get_time());
// long long int min;
// int i;
// i = 0;
// min = philo[philo->pos].lst_meal;
// while (i < philo->args->num_philo)
// {
// 	if (min > get_time() - philo->lst_meal)
// }
// if (philo->pos % 2 == 0 && philo->args->num_philo != 1)
// {
// }

int	start(t_args *args)
{
	long long int		i;

	i = 0;
	args->time = get_time();
	while (i < args->num_philo)
	{
		args->philos[i].lst_meal = get_time();
		if (pthread_create(&args->tids[i], NULL, &routine, \
		(void *)&args->philos[i]))
			return (ft_log(PTHREAD_ERROR));
		i++;
	}
	return (0);
}

int	even_philos_taking_fork(t_philo *philo)
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
		while (1)
		{
			pthread_mutex_lock(&philo->args->die_mutex);
			if (philo->args->dead)
				break ;
			pthread_mutex_unlock(&philo->args->die_mutex);
		}
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->pos % 2 == 0)
		return (even_philos_taking_fork(philo));
	else
	{
		pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
		ft_msg(philo, TAKING_FORK);
		philo->args->forks[philo->r_frk] = 1;
		pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
		ft_msg(philo, TAKING_FORK);
		philo->args->forks[philo->l_frk] = 1;
	}
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->eating_mutex);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->args->eating_mutex);
	pthread_mutex_lock(&philo->args->ls_meal_mutex);
	philo->lst_meal = get_time();
	pthread_mutex_unlock(&philo->args->ls_meal_mutex);
	ft_msg(philo, EATING);
	ft_usleep(philo->args->eat_time);
	pthread_mutex_lock(&philo->args->eating_mutex);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->args->eating_mutex);
	philo->num_of_meals += 1;
	if (philo->args->num_to_eat > 0 && \
	(long long int)philo->num_of_meals >= philo->args->num_to_eat)
	{
		ft_msg(philo, OVER);
		philo->args->forks[philo->l_frk] = 0;
		pthread_mutex_unlock(&philo->args->forks_mutexes[philo->l_frk]);
		philo->args->forks[philo->r_frk] = 0;
		pthread_mutex_unlock(&philo->args->forks_mutexes[philo->r_frk]);
		philo->args->finished++;
		return (1);
	}
	return (0);
}

void	*routine(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	if (philo->pos % 2 == 0 && philo->args->num_philo != 1)
		ft_usleep(philo->args->eat_time);
	while (1)
	{
		pthread_mutex_lock(&philo->args->die_mutex);
		if (philo->args->dead)
		{
			pthread_mutex_unlock(&philo->args->die_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->die_mutex);
		if (take_forks(philo) || eat(philo) || release_forks(philo))
			break ;
	}
	return (NULL);
}
