#include "philo.h"

long long int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long int ms)
{
	long long int	end;

	end = get_time() + ms;
	while (get_time() <= end)
	{
		usleep(50);
	}
}
