/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:47:02 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/28 19:18:00 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_args *args)
{
	long long int	i;

	args->forks_mutexes = malloc(sizeof(pthread_mutex_t)
			* args->num_philo);
	if (!args->forks_mutexes)
		return (ft_err(MALLOC_ERROR));
	i = 0;
	while (i < args->num_philo)
	{
		pthread_mutex_init(&args->forks_mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->wr_mutex, NULL);
	pthread_mutex_init(&args->die_mutex, NULL);
	pthread_mutex_init(&args->ls_meal_mutex, NULL);
	pthread_mutex_init(&args->eating_mutex, NULL);
	return (0);
}

int	init_args(t_args *args, int argc, char **argv)
{
	if (argc > 6)
		return (ft_err(TOO_MANY_ARGUMENTS));
	if (argc < 5)
		return (ft_err(NOT_ENOUGH_ARGUMENTS));
	args->num_philo = ft_atoi(argv[1]);
	args->death_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (args->num_philo <= 0 || args->death_time <= 0 || args->eat_time <= 0 \
		|| args->sleep_time <= 0)
		return (ft_err(WRONG_ARGUMENT));
	if (argc == 6)
	{
		args->num_to_eat = ft_atoi(argv[5]);
		if (args->num_to_eat <= 0)
			return (ft_err(WRONG_ARGUMENT));
	}
	else if (argc == 5)
		args->num_to_eat = -1;
	args->finished = 0;
	args->dead = 0;
	args->philo_pos = 0;
	return (0);
}

// 0 mod 5 = 0
// 1 mod 5 = 1
// 2 mod 5 = 2
// 3 mod 5 = 3
// 4 mod 5 = 4
// 5 mod 5 = 0

// if the number on the left handside of the mod operator 
// is less than the number on the right side, the result will
// be the number on the left handside
// if both numbers are same, the result will be zero
int	init_philos(t_args *args)
{
	long long int	i;

	args->philos = malloc(sizeof(t_philo) * args->num_philo);
	args->forks = malloc(sizeof(int) * args->num_philo);
	args->tids = malloc(sizeof(pthread_t) * args->num_philo);
	if (!args->philos || !args->forks || !args->tids)
		return (ft_err(MALLOC_ERROR));
	i = 0;
	while (i < args->num_philo)
	{
		args->forks[i] = 0;
		args->philos[i].pos = i;
		args->philos[i].l_frk = i;
		args->philos[i].r_frk = (i + 1) % args->num_philo;
		args->philos[i].num_of_meals = 0;
		args->philos[i].eating = 0;
		args->philos[i].args = args;
		args->philos->lst_meal = 0;
		args->forks[i] = 0;
		i++;
	}
	return (0);
}

/*
    TODO   :
    *arg 1 :number_of_philosophers 
    *arg 2 :time_to_die 
    *arg 3 :time_to_eat
    *arg 4 :time_to_sleep
    *arg 5 :[number_of_times_each_philosopher_must_eat]
*/

// this function monitos if an of the philos exceeded death time
// it gets the current time and substracts the time philo had 
//	their last meal 
// if the resulting time is greater than the death time,it means 
// they are gonna die
// so i will set the death flag, so that any other philos wont be 
//	able to print any msg
// it the optinal argument is given it also checks if each philo
// has finished eating

void	monitor(t_args *args)
{
	long long int	i;
	long long int	time_left;
	int				eating;

	while (1)
	{
		i = 0;
		while (i < args->num_philo)
		{
			set_timeleft_eating(args, &time_left, &eating, i);
			if (get_time() - time_left > args->death_time && !eating)
			{	
				ft_msg(&args->philos[i], DIED);
				return ;
			}
			if ((long long int)args->finished == args->num_philo)
				return ;
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_args			args;
	long long int	i;

	if (init_args(&args, argc, argv) || init_philos(&args) || \
		init_mutexes(&args))
		return (1);
	start(&args);
	monitor(&args);
	i = 0;
	while (i < args.num_philo)
	{
		pthread_join(args.tids[i], NULL);
		i++;
	}
	i = 0;
	while (i < args.num_philo)
	{
		pthread_mutex_destroy(&args.forks_mutexes[i]);
		i++;
	}
	waitchildthreads_and_destorymutex(&args);
	return (0);
}
