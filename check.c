/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:53:09 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 19:46:18 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_all_philo_eat(t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	i = 1 + (philo->id_philo * -1);
	while (j < philo->nbr_of_philo)
	{
		pthread_mutex_lock(&philo[i].time_eat);
		if (philo[i].nbr_of_times_philo_must_eat > 0)
		{
			pthread_mutex_unlock(&philo[i].time_eat);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].time_eat);
		i++;
		j++;
	}
	if (philo->if_ac == 6)
	{
		pthread_mutex_lock(&philo->philo_state);
		philo->state = 1;
		pthread_mutex_unlock(&philo->philo_state);
	}
	return (0);
}

int	check_state(t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	i = 1 + (philo->id_philo * -1);
	while (j < philo->nbr_of_philo)
	{
		pthread_mutex_lock(&philo[i].philo_state);
		if (philo[i].state != 0)
		{
			pthread_mutex_unlock(&philo[i].philo_state);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].philo_state);
		i++;
		j++;
	}
	return (1);
}

int	only_1(t_philo *philo)
{
	if_print(philo, " Has taken a fork");
	pthread_mutex_unlock(philo->mutex_eat_dead);
	if (ft_sleep(philo, philo->time_to_die) == -1)
		return (-1);
	time_to_die(philo);
	return (0);
}
