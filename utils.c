/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:37:47 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 18:08:46 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned  int	ft_atoi(char *str)
{
	int	neg;
	int	i;
	int	num;

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

unsigned int	time_diff(struct timeval *start, struct timeval *end)
{
	return ((unsigned int)(1000 * end->tv_sec + 0.001 * end->tv_usec) - \
	(1000 * start->tv_sec + 0.001 * start->tv_usec));
}

int	ft_sleep(t_philo *philo, int time_of_sleep)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	unsigned int cur = (unsigned int)(1000 * tv.tv_sec + 0.001 * tv.tv_usec);
	unsigned int end = cur + time_of_sleep;
	while (cur < end)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		cur = (unsigned int)(1000 * tv.tv_sec + 0.001 * tv.tv_usec);
		if (time_to_die(philo) == -1)
			return(-1);
	}
	return (0);
}
