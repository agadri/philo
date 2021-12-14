/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:25:32 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 20:09:33 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putnbr(long long n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

int	if_print(t_philo *philo, char *str)
{
	unsigned int	tv;

	pthread_mutex_lock(philo->mutex_eat_dead);
	if (check_state(philo) == 0)
		return (-1);
	gettimeofday(&philo->time.time_print, NULL);
	tv = time_diff(&philo->time.time_all, &philo->time.time_print);
	ft_putnbr(tv);
	ft_putstr(" philo: ");
	ft_putnbr(philo->id_philo);
	ft_putstr(str);
	ft_putchar('\n');
	return (0);
}
