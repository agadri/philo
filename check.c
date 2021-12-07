/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:53:09 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/07 20:02:15 by adegadri         ###   ########.fr       */
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
		if (philo[i].nbr_of_times_philo_must_eat > 0)
		{
			philo->state = 0;
			return (1);
		}
		i++;
		j++;
	}
	if (philo->if_ac == 6)
	{
		philo->state = 1;
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
		if (philo[i].state != 0)
		{
			return (0);
		}
		i++;
		j++;
	}
	return (1);
}
