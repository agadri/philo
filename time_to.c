/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:38:12 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 20:30:44 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_eat(t_philo *philo)
{
	int	ret;

	ret = when_take_fork(philo);
	if (ret != 0)
		return (ret);
	if (time_to_die(philo) == -1)
		return (-1);
	gettimeofday(&philo->time.time_meal_start, NULL);
	if ((if_print(philo, " is eating") == -1) & \
	(!pthread_mutex_unlock(philo->mutex_eat_dead)))
		return (-1);
	pthread_mutex_lock(&philo->time_eat);
	philo->nbr_of_times_philo_must_eat -= 1;
	pthread_mutex_unlock(&philo->time_eat);
	check_if_all_philo_eat(philo);
	gettimeofday(&philo->time.time_die_start, NULL);
	if (ft_sleep(philo, philo->time_to_eat) == -1)
		return (-1);
	return (0);
}

int	time_to_sleep(t_philo *philo)
{
	pthread_mutex_unlock (philo->left);
	pthread_mutex_unlock (&philo->mutex_fourchette);
	if (time_to_die(philo) == -1)
		return (-1);
	gettimeofday(&philo->time.time_sleep_start, NULL);
	if ((if_print(philo, " is sleeping") == -1) & \
	(!pthread_mutex_unlock(philo->mutex_eat_dead)))
		return (-1);
	if (ft_sleep(philo, philo->time_to_sleep) == -1)
		return (-1);
	return (0);
}

int	time_to_think(t_philo *philo)
{	
	if (time_to_die(philo) == -1 || check_state(philo) == 0)
		return (-1);
	gettimeofday(&philo->time.time_sleep_end, NULL);
	philo->time.timer = time_diff(&philo->time.time_sleep_start, \
	&philo->time.time_sleep_end);
	if ((if_print(philo, " is thinking") == -1) & \
	(!pthread_mutex_unlock(philo->mutex_eat_dead)))
		return (-1);
	return (0);
}

int	time_to_die(t_philo *philo)
{
	int				i;
	int				j;
	unsigned int	tv;

	j = -1;
	i = 1 + (philo->id_philo * -1);
	while (++j < philo->nbr_of_philo)
	{
		gettimeofday(&philo[i].time.time_die_end, NULL);
		tv = time_diff(&philo[i].time.time_die_start, \
		&philo[i].time.time_die_end);
		if (tv >= philo[i].time_to_die)
		{
			if (if_print(&philo[i], " died") == -1 && \
			!pthread_mutex_unlock(philo[i].mutex_eat_dead))
				return (-1);
			pthread_mutex_lock(&philo[i].philo_state);
			philo[i].state = 1;
			pthread_mutex_unlock(&philo[i].philo_state);
			pthread_mutex_unlock(philo[i].mutex_eat_dead);
			return (-1);
		}
		i++;
	}
	return (0);
}
