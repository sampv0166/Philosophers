/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:47:45 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/28 14:44:07 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->r_frk]);
	philo->args->forks[philo->r_frk] = 0;
	pthread_mutex_unlock(&philo->args->forks_mutexes[philo->r_frk]);
	pthread_mutex_lock(&philo->args->forks_mutexes[philo->l_frk]);
	philo->args->forks[philo->l_frk] = 0;
	pthread_mutex_unlock(&philo->args->forks_mutexes[philo->l_frk]);
	ft_msg(philo, SLEEPING);
	ft_usleep(philo->args->sleep_time);
	ft_msg(philo, THINKING);
	return (0);
}

// get time function returns a struct with 2 values in it
// one is micro seconds and seconds elapsed since 
// tv.tv_sec = seconds | tv.tv_usec = micro seconds
// 1 second == 1000 milli second 
// 1 millisecond = 1000 microsecond
// to get the exact value in milli seconds, we add both of
// these values by converting them to milli seconds

long long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// this function pauses the calling thread to stop execution with the
// specified time
// get the starting time
// time to sleep  == 100
// get starting time == 200
// when current time == 301
// 301 - 200 < 101 exits the loop
// usleep takes microseconds as parameter
// while both with achieve what you're trying to do,
// the while loop will keep the processor occupied, consuming CPU time.
// usleep() frees the processor for the amount of time mentioned.
void	ft_usleep(long long int ms)
{
	long long int	start_time;

	start_time = get_time();
	while (get_time() - start_time < ms)
		usleep(100);
}
