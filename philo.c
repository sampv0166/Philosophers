#include "philo.h"

long get_time()
{
    struct timeval tv;
    long res;

    gettimeofday(&tv, NULL);
    res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
    return(res);
}

void *execute_thread()
{

}    

int init_philo (char **argv , t_args *args)
{
    // args = malloc (sizeof (t_philo_args) * num + 1); 
    // init_philo(args, num); 

    int i;

    i = 0 ;
    while (argv[i])
    {
        if (ft_atoi(argv[i]) < 0)
            return (1);
        i++;
    }
    args->num_philo =ft_atoi(argv[1]);
    args->death_time = ft_atoi(argv[2]);
    args->eat_time = ft_atoi(argv[3]);
    args->sleep_time = ft_atoi(argv[4]);
    args->num_to_eat = ft_atoi(argv[5]);
    return (0);
}

void print_number(int i, char *str)
{
    printf("\n%s = %d\n", str, i);
}

void create_philo_threads(t_args *args)
{
    int i;

    i = 0;

    pthread_t *threads;
    threads = malloc (sizeof (pthread_t) * (args->num_philo));
    while (i < args->num_philo)
    {
        pthread_create(&threads[i], NULL, execute_thread, (void *)&args->philos[i]);
        i++;
    }
}

void init_fork_mutex(t_args *args)
{
    int i;
    pthread_mutex_t *fork_mutex;

    i = 0;
    fork_mutex = malloc(sizeof(pthread_mutex_t) * (args->num_philo));
    while (i < args->num_philo)
    {
       pthread_mutex_init(&fork_mutex[i], NULL);
        i++;
    }
    args->forks = fork_mutex;   
}

void init_philo(t_args *args)
{
    int i;

    i = 0 ;

    args->philos = malloc (sizeof ( t_philo) * args->num_philo);
    while (i < args->philos)
    {
        args->philos[i].num_philo = args->num_philo;
        args->philos[i].eat_time = args->eat_time;
        args->philos[i].death_time = args->death_time;
        args->philos[i].sleep_time = args->sleep_time;
        args->philos[i].num_to_eat = args->num_to_eat;
        args->philos[i].last_meal_time = get_time();
        i++;
    }
}

int main (int argc, char **argv)
{
    t_args args;
    
    /*
    TODO   :
    *arg 1 :number_of_philosophers 
    *arg 2 :time_to_die 
    *arg 3 :time_to_eat
    *arg 4 :time_to_sleep
    *arg 5 :[number_of_times_each_philosopher_must_eat]
    */

   	if (argc < 5 || argc > 6 || init_philo(argv, &args))
		return (0);
    init_fork_mutex(&args);
    init_philo(argv, &args);
    create_philo_threads(&args);
    
    print_number(args.num_philo, "num_philo"); 
    print_number(args.death_time, "death_time"); 
    print_number(args.eat_time, "eat_time");
    print_number(args.sleep_time, "sleep_time");
    print_number(args.num_to_eat, "num_of_times_should_eat");

}