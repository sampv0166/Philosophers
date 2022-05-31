#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

# define WRONG_ARGUMENT -1
# define TOO_MANY_ARGUMENTS -2
# define MALLOC_ERROR -3
# define PTHREAD_ERROR -4
# define NOT_ENOUGH_ARGUMENTS -5

struct	s_philo;

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	OVER,
}				t_action;

typedef struct s_args
{
	size_t			num_philo;
	size_t			eat_time;
	size_t			death_time;
	size_t			sleep_time;
	size_t			num_to_eat;
	size_t			finished;
	int				*forks;
	pthread_mutex_t	*forks_mutexes;
	pthread_mutex_t	wr_mutex;
	pthread_mutex_t	die_mutex;
	struct s_philo	*philos;
	pthread_t 		*tids;
	int				dead;
}					t_args;

typedef struct s_philo
{
	size_t		pos;
	size_t		l_frk;
	size_t		r_frk;
	size_t		num_of_meals;
	size_t		eating;
	size_t		lst_meal;
	size_t		max;
	size_t		max_time;
	t_args		*args;
	t_args		philo_args;
	int			dead_philo;
}				t_philo;

int		ft_isdigit(int val);
int		ft_atoi(const char *str, size_t *num);
int		ft_err(int	error);
void	*routine(void *philo_t);
void	ft_msg(t_philo *philo, size_t timestamp, int action);
int	ft_log(int	error);
size_t	get_time(void);
void	ft_usleep(size_t ms);
#endif