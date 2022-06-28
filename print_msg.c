/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:47:21 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/28 19:18:08 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_log(int error)
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

void	set_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->die_mutex);
	philo->args->dead = 1;
	pthread_mutex_unlock(&philo->args->die_mutex);
	printf("%lld - philo %ld died 💀\n", \
	philo->args->time - get_time(), philo->pos);
}

void	print_msg(t_philo *philo, char *msg)
{
	printf("%lld  %ld %s\n", philo->args->time - get_time(), philo->pos, msg);
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
		print_msg(philo, "has taken a fork 🍽");
	else if (action == EATING)
		print_msg(philo, "is eating 🍕");
	else if (action == SLEEPING)
		print_msg(philo, "is sleeping 💤");
	else if (action == THINKING)
		print_msg(philo, "is thinking 💭");
	else if (action == OVER)
		print_msg(philo, "has finished his meals 🤢");
	else if (action == DIED)
	{
		set_philo_died(philo);
		pthread_mutex_unlock(&philo->args->wr_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->args->wr_mutex);
}
