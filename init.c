/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:51:48 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 18:47:28 by adegadri         ###   ########.fr       */
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
		else
			stock->philo[i].left = &(stock->philo[i - 1].mutex_fourchette);
		i++;
	}
}

int	init_mutex(t_stock *stock)
{
	int	i;

	i = 0;
	stock->philo->mutex_eat_dead = malloc(sizeof(pthread_mutex_t) * 1);
	if (!stock->philo->mutex_eat_dead)
		return (-1);
	pthread_mutex_init(stock->philo->mutex_eat_dead, NULL);
	while (i < stock->nb_philo)
	{
		gettimeofday(&stock->philo[i].time.time_all, NULL);
		pthread_mutex_init(&stock->philo[i].mutex_fourchette, NULL);
		pthread_mutex_init(&stock->philo[i].mutex_init, NULL);
		pthread_mutex_init(&stock->philo[i].time_eat, NULL);
		pthread_mutex_init(&stock->philo[i].time_write, NULL);
		pthread_mutex_init(&stock->philo[i].philo_state, NULL);
		stock->philo[i].mutex_eat_dead = stock->philo->mutex_eat_dead;
		i++;
	}
	return (0);
}

int	ft_malloc_all(t_stock *stock)
{
	stock->philo = malloc(sizeof(t_philo) * stock->nb_philo);
	if (!stock->philo)
		return (1);
	stock->fourchette = malloc(sizeof(t_fork) * stock->nb_philo);
	if (!stock->fourchette)
		return (1);
	return (0);
}

int	init_timer(t_stock *stock, int ac, char **av)
{
	int	i;

	i = 0;
	
	while (i < stock->nb_philo)
	{
		if (ac >= 5)
		{
			gettimeofday(&stock->philo[i].time.time_die_start, NULL);
			
			stock->philo[i].id_philo = i + 1;
			stock->philo[i].time_to_die = ft_atoi(av[2]);
			stock->philo[i].time_to_eat = ft_atoi(av[3]);
			stock->philo[i].time_to_sleep = ft_atoi(av[4]);
			stock->philo[i].time.timer = .0;
			stock->philo[i].nbr_of_philo = stock->nb_philo;
			stock->philo[i].state = 0;
			stock->philo[i].if_ac = ac;
			stock->philo[i].nbr_of_times_philo_must_eat = 1;
		}
		if (ac == 6)
			stock->philo[i].nbr_of_times_philo_must_eat = ft_atoi(av[5]);
		i++;
	}
	return (0);
}

void	ft_free_all(t_stock *stock)
{
	if (stock->philo->mutex_eat_dead)
		free(stock->philo->mutex_eat_dead);
	free(stock->philo);
	if (stock->fourchette)
		free(stock->fourchette);
}
