#include "philo.h"

int	start(t_args *args)
{
	size_t		i;
	pthread_t	tid;

	i = 0;
	// pthread_mutex_lock(&args->die_mutex);
	while (i < args->num_philo)
	{
		if (pthread_create(&tid, NULL, &routine,
				(void *)&args->philos[i]))
			return (ft_log(PTHREAD_ERROR));
		i++;
	}
	return (0);
}

int	init_mutexes(t_args *args)
{
	size_t	i;

	args->forks_mutexes = malloc(sizeof(pthread_mutex_t)
			* args->num_philo);
	if (!args->forks_mutexes)
		return (ft_log(MALLOC_ERROR));
	i = 0;
	while (i < args->num_philo)
	{
		pthread_mutex_init(&args->forks_mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->wr_mutex, NULL);
	pthread_mutex_init(&args->die_mutex, NULL);
	return (0);
}

int init_args(t_args *args, int argc, char **argv)
{
	if (argc > 6)
		return (ft_err(TOO_MANY_ARGUMENTS));
	if (argc < 5)
		return (ft_err(NOT_ENOUGH_ARGUMENTS));
	if (ft_atoi(argv[1], &args->num_philo) || args->num_philo == 0
		|| ft_atoi(argv[2], &args->death_time) || args->death_time == 0
		|| ft_atoi(argv[3], &args->eat_time) || args->eat_time == 0
		|| ft_atoi(argv[4], &args->sleep_time) || args->sleep_time == 0)
		return (ft_err(WRONG_ARGUMENT));
	if (argc == 6 && (ft_atoi(argv[5], &args->num_to_eat)
			|| args->num_to_eat == 0))
		return (ft_err(WRONG_ARGUMENT));
	else if (argc == 5)
		args->num_to_eat= -1;
	args->finished = 0;
	return (0);
}


int init_philos(t_args *args)
{
	size_t	i;

	args->philos = malloc(sizeof(t_philo) * args->num_philo);
	args->forks = malloc(sizeof(int) * args->num_philo);
	if (!args->philos || !args->forks)
		return (ft_log(MALLOC_ERROR));
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
		i++;
	}
	return (0);
}

// void wait_for_threads(t_args *arg)
// {
//     int i;

//     i = 0;
//     while (i < arg->num_philo)
//     {
//         pthread_join(arg->thread_ids[i], NULL);
//         i++;
//     }
// }
/*
    TODO   :
    *arg 1 :number_of_philosophers 
    *arg 2 :time_to_die 
    *arg 3 :time_to_eat
    *arg 4 :time_to_sleep
    *arg 5 :[number_of_times_each_philosopher_must_eat]
*/

int	main (int argc, char **argv)
{
	t_args	args;

	if (init_args(&args, argc, argv)
		|| init_philos(&args)
		|| init_mutexes(&args))
		return (1);
	if (start(&args))
		return (1);
}


    // init_fork_mutex(&args);
    // init_philo(&args);
    // create_philo_threads(&args);
    // wait_for_threads(&args);

    // print_number(args.num_philo, "num_philo"); 
    // print_number(args.death_time, "death_time"); 
    // print_number(args.eat_time, "eat_time");
    // print_number(args.sleep_time, "sleep_time");
    // print_number(args.num_to_eat, "num_of_times_should_eat");