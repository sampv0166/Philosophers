#include "philo.h"

int	start(t_args *args)
{
	long long int		i;

	i = 0;
	args->time = get_time();
	while (i < args->num_philo)
	{
		args->philos[i].lst_meal = get_time();
		
		if (pthread_create(&args->tids[i] , NULL, &routine,(void *)&args->philos[i]))
			return (ft_log(PTHREAD_ERROR));
		i++;
	}
	return (0);
}

int	init_mutexes(t_args *args)
{
	long long int	i;

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
	args->dead  = 0;
	args->philo_pos = 0;
	return (0);
}

int init_philos(t_args *args)
{
	long long int	i;

	args->philos = malloc(sizeof(t_philo) * args->num_philo);
	args->forks = malloc(sizeof(int) * args->num_philo);
	args->tids = malloc(sizeof(pthread_t) * args->num_philo);
	if (!args->philos || !args->forks || !args->tids)
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
		args->philos[i].thinking = 0;
		args->philos->lst_meal = 0;
		args->forks[i] = 0;
		args->philos[i].just_ate = 0;
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

int	waitChildThreads_and_destoryMutex(t_args *args)
{
	pthread_mutex_destroy(&args->wr_mutex);
	free(args->forks_mutexes);
	free(args->philos);
	free(args->forks);
	free(args->tids);
	return (0);
}

void monitor (t_args *args)
{
	long long int	i;
	i = 0;
//	printf("\nargs.lastmeall = %lld\n", args->philos[0].lst_meal);
	while (1)
	{
		i = 0;
		while (i < args->num_philo)
		{
			if (get_time() - args->philos[i].lst_meal > args->death_time)
			{				
				//printf("\n%lld >  %lld\n", (get_time() - args->philos[i].lst_meal),args->death_time);
				pthread_mutex_lock(&args->wr_mutex);
				args->dead = 1;
				printf("%lld - philo %ld dies 💀\n",args->time - get_time(), args->philos[i].pos);
				pthread_mutex_unlock(&args->wr_mutex);
				return ;
			}
			if ((long long int)args->finished == args->num_philo)
				return ;
			i++;
		}
	}
}

int	main (int argc, char **argv)
{
	t_args	args;
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
		pthread_mutex_destroy(&args.forks_mutexes[i]);
		i++;
	}
	waitChildThreads_and_destoryMutex(&args);
	return (0);
}
