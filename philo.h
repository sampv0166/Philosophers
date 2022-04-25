#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    int num_philo;
    int eat_time;
    int death_time;
    int sleep_time;
    int num_to_eat;
    int last_meal_time;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
}               t_philo;


typedef struct s_args
{
    int num_philo;
    int eat_time;
    int death_time;
    int sleep_time;
    int num_to_eat;
    pthread_t *thread_ids;
    pthread_mutex_t *forks;
    t_philo *philos;
}              t_args;

int	ft_isdigit(int val);

int	ft_atoi(const char *str);

#endif