/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_time_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:01:30 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 16:07:03 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	when_take_fork(t_philo *philo)
{
	if (philo->nbr_of_philo == 1 && !only_1(philo))
		return (-4);
	if (philo->id_philo % 2)
	{
		pthread_mutex_lock (philo->left);
		if (if_print(philo, " Has taken a fork") == -1)
			return (-3);
		pthread_mutex_lock (&philo->mutex_fourchette);
		if (if_print(philo, " Has taken a fork") == -1)
			return (-1);
	}
	else
	{
		pthread_mutex_lock (&philo->mutex_fourchette);
		if (if_print(philo, " Has taken a fork") == -1)
			return (-2);
		pthread_mutex_lock (philo->left);
		if (check_state(philo) == 0)
			return (-1);
		if (if_print(philo, " Has taken a fork") == -1)
			return (-1);
	}
	return (0);
}
