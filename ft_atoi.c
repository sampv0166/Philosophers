/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:44:09 by apila-va          #+#    #+#             */
/*   Updated: 2022/06/20 17:49:13 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

void	init(size_t *i, int *s, size_t *res)
{
	*i = 0;
	*s = 1;
	*res = 0;
}

void	skip_sapces_and_signs(const char *str, size_t *i, int *s)
{
	while (str && (str[(*i)] == ' ' || str[(*i)] == '\n' || \
		str[(*i)] == '\t' || \
		str[(*i)] == '\v' || str[(*i)] == '\f' || str[(*i)] == '\r'))
		(*i)++;
	if (str && (str[(*i)] == '-' || str[(*i)] == '+'))
	{
		if (str[(*i)] == '-')
			*s = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		s;
	size_t	res;

	init(&i, &s, &res);
	if (ft_strlen(str) == 1 && (*str == '-' || *str == '+'))
		return (0);
	skip_sapces_and_signs(str, &i, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		if ((res > 2147483647 && s == 1))
			return (-1);
		if ((res > 2147483648 && s == -1))
			return (0);
	}
	if (str[i] != '\0')
		return (0);
	return (res * s);
}
