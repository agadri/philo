/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:51:48 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/07 20:02:43 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_left_right(t_stock *stock)
{
	int	i;

	i = 0;
	while (i < stock->nb_philo)
	{
		if (i == 0)
			stock->philo[i].left = \
			&(stock->philo[stock->nb_philo - 1].mutex_fourchette);
		else if (i == stock->nb_philo - 1)
			stock->philo[i].left = &(stock->philo[i - 1].mutex_fourchette);
		else
			stock->philo[i].left = &(stock->philo[i - 1].mutex_fourchette);
		i++;
	}
}

int	init_timer(t_stock *stock, int ac, char **av)
{
	int	i;

	i = 0;
	stock->nb_philo = ft_atoi(av[1]);
	while (i < stock->nb_philo)
	{
		if (ac >= 5)
		{
			stock->philo[i].id_philo = i + 1;
			stock->philo[i].time_to_die = ft_atoi(av[2]);
			stock->philo[i].time_to_eat = ft_atoi(av[3]);
			stock->philo[i].time_to_sleep = ft_atoi(av[4]);
			stock->philo[i].nbr_of_philo = stock->nb_philo;
			stock->philo[i].state = 0;
			stock->philo[i].if_ac = ac;
		}
		if (ac == 6)
			stock->philo[i].nbr_of_times_philo_must_eat = ft_atoi(av[5]);
		i++;
	}
	return (0);
}

int	ft_malloc_all(t_stock *stock)
{
	stock->stock = 6;
	stock->philo = malloc(sizeof(t_philo) * stock->nb_philo);
	if (!stock->philo)
		return (1);
	stock->fourchette = malloc(sizeof(t_fork) * stock->nb_philo);
	if (!stock->fourchette)
		return (1);
	return (0);
}
