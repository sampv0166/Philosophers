/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:56:33 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/28 18:55:15 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_timeleft_eating(t_args *args, long long int *time_left, \
		int *eating, long long int i)
{
	pthread_mutex_lock(&args->ls_meal_mutex);
	*time_left = args->philos[i].lst_meal;
	pthread_mutex_unlock(&args->ls_meal_mutex);
	pthread_mutex_lock(&args->eating_mutex);
	*eating = args->philos[i].eating;
	pthread_mutex_unlock(&args->eating_mutex);
}

int	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
	philo->args->forks[philo->r_frk] = 1;
	ft_msg(philo, TAKING_FORK);
	pthread_mutex_unlock(&philo->args->forks_mutexes[philo->r_frk]);
	while (1)
	{
		pthread_mutex_lock(&philo->args->die_mutex);
		if (philo->args->dead)
		{
			pthread_mutex_unlock(&philo->args->die_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->die_mutex);
	}
	return (1);
}

void	set_right_fork_status(t_philo *philo)
{
	ft_msg(philo, TAKING_FORK);
	philo->args->forks[philo->r_frk] = 1;
}

void	set_left_fork_status(t_philo *philo)
{
	ft_msg(philo, TAKING_FORK);
	philo->args->forks[philo->l_frk] = 1;
}
