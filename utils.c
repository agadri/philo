#include "philo.h"

int		ft_atoi(char *str)
{
	int neg;
	int i;
	int num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

float time_diff(struct timeval *start, struct timeval *end)
{
	//printf("time   %f\n", ((0.001 * end->tv_sec) + 1000 * end->tv_sec) - (0.001 * start->tv_sec) + 1000 * start->tv_sec);
	return ((1000 * end->tv_sec + 0.001 * end->tv_usec) - (1000 * start->tv_sec + 0.001 * start->tv_usec));
}
