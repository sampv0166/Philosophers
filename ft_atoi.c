/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:35:41 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/20 12:35:46 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, long long int *num)
{
	int	i;


	i = 0;
	if (str[i] == '\0')
		return (1);
	*num = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		*num = *num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (1);
	return (0);
}