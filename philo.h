/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:47:13 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/21 15:29:41 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
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
	long long int		num_philo;
	long long int		eat_time;
	long long int		death_time;
	long long int		sleep_time;
	long long int		num_to_eat;
	size_t				finished;
	int					*forks;
	pthread_mutex_t		*forks_mutexes;
	pthread_mutex_t		wr_mutex;
	pthread_mutex_t		die_mutex;
	pthread_mutex_t		ls_meal_mutex;
	pthread_mutex_t		eating_mutex;
	struct s_philo		*philos;
	pthread_t			*tids;
	int					dead;
	int					num_meals_fnished;
	int					philo_pos;
	long long int		time;
}					t_args;

typedef struct s_philo
{
	size_t			pos;
	size_t			l_frk;
	size_t			r_frk;
	size_t			num_of_meals;
	size_t			eating;
	long long int	lst_meal;
	long long int		max;
	long long int		max_time;
	t_args		*args;
	t_args		philo_args;
	int			dead_philo;
	int			thinking;
	int 		just_ate;
}				t_philo;

int				ft_isdigit(int val);
int				ft_atoi(const char *str);
int				ft_err(int error);
void			*routine(void *philo_t);
void			ft_msg(t_philo *philo, int action);
int				ft_log(int error);
long long int	get_time(void);
void			ft_usleep(long long int ms);
int				start(t_args *args);
int				waitchildthreads_and_destorymutex(t_args *args);
int				release_forks(t_philo *philo);
#endif
