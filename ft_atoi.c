#include "philo.h"

int	ft_atoi(const char *str, size_t *num)
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