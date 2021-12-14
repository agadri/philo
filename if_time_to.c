/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_time_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:01:30 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 20:37:06 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_modulo2(t_philo *philo)
{
	pthread_mutex_lock (philo->left);
	if ((if_print(philo, " Has taken a fork") == -1) & \
	(!pthread_mutex_unlock(philo->mutex_eat_dead)))
		return (-3);
	pthread_mutex_lock (&philo->mutex_fourchette);
	if ((if_print(philo, " Has taken a fork") == -1) & \
	(!pthread_mutex_unlock(philo->mutex_eat_dead)))
		return (-1);
	return (0);
}

int	if_not_modulo2(t_philo *philo)
{
	pthread_mutex_lock (&philo->mutex_fourchette);
	if ((if_print(philo, " Has taken a fork") == -1) & \
	(!pthread_mutex_unlock(philo->mutex_eat_dead)))
		return (-2);
	pthread_mutex_lock (philo->left);
	if (check_state(philo) == 0)
		return (-1);
	if ((if_print(philo, " Has taken a fork") == -1) & \
	(!pthread_mutex_unlock(philo->mutex_eat_dead)))
		return (-1);
	return (0);
}

int	when_take_fork(t_philo *philo)
{
	int	ret;

	if (philo->nbr_of_philo == 1 && !only_1(philo))
		return (-4);
	if (philo->id_philo % 2)
	{
		ret = if_modulo2(philo);
		if (ret == -3)
			return (-3);
		if (ret == -1)
			return (-1);
	}
	else
	{
		ret = if_not_modulo2(philo);
		if (ret == -2)
			return (-2);
		if (ret == -1)
			return (-1);
	}
	return (0);
}
