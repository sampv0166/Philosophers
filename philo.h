/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:47:13 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/28 16:33:13 by apila-va         ###   ########.fr       */
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

// number of philos /  number of forks /  number of threads
// time each philo has to eat
// time philo should die if didnt eat
// time each philo has to sleep
// number of time to eat (optional)
//finished is used to check if each philo had done eating
// forks as integer array
// mutex to protect the data in the fork array
// wr mutex, so that msg dont get mixe up
// die mutex , stops other threads from printing once a -
// philo has idefntifed dead
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
	int					philo_pos;
	long long int		time;
}					t_args;

// stores the position of the philo
// fork number on the left
// fork number on the right
// num_of_meals philo should eat (optional)
// eating status
// the time of last meal
// pointer to the args values, so that each philo has values of eattime,
// sleeptime etc.....

typedef struct s_philo
{
	size_t			pos;
	size_t			l_frk;
	size_t			r_frk;
	size_t			num_of_meals;
	size_t			eating;
	long long int	lst_meal;
	t_args			*args;
}				t_philo;

int				ft_isdigit(int val);
int				ft_atoi(const char *str);
// prints any kind of error if it happens
int				ft_err(int error);
// this function specifes what each thread should do.
void			*routine(void *philo_t);
// display the appropriate msg of what the philos are doing .
void			ft_msg(t_philo *philo, int action);
// gets the current time in milliseconds
long long int	get_time(void);
// paueses the calling thread for specifed time
void			ft_usleep(long long int ms);
// stores the time when the thereads are created
// creates each thread in w while loop passing thread_id, thread_routine and 
// the data 
int				start(t_args *args);
// destory mutex and free the malloced valules
int				waitchildthreads_and_destorymutex(t_args *args);
int				release_forks(t_philo *philo);
int				handle_one_philo(t_philo *philo);
void			set_right_fork_status(t_philo *philo);
void			set_left_fork_status(t_philo *philo);
void			set_timeleft_eating(t_args *args, long long int *time_left, \
				int *eating, long long int i);
#endif