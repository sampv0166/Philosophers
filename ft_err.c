/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:46:42 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/20 17:51:21 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_err(int error)
{
	if (error == NOT_ENOUGH_ARGUMENTS)
		printf("Error: Not Enough argumens.\n");
	else if (error == WRONG_ARGUMENT)
		printf("Error: Wrong argument.\n");
	else if (error == TOO_MANY_ARGUMENTS)
		printf("Error: Wrong syntax.\n");
	else if (error == MALLOC_ERROR)
		printf("Error: Malloc error.\n");
	else if (error == PTHREAD_ERROR)
		printf("Error: PThread error.\n");
	return (1);
}

int	waitchildthreads_and_destorymutex(t_args *args)
{
	pthread_mutex_destroy(&args->wr_mutex);
	free(args->forks_mutexes);
	free(args->philos);
	free(args->forks);
	free(args->tids);
	return (0);
}
