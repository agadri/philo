/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:38:12 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/07 20:09:18 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_eat(t_philo *philo)
{
	int	ret_mutex1;
	int	ret_mutex2;

	ret_mutex1 = pthread_mutex_lock (philo->left);
	printf("philo %d prend la fourchette de gauche\n", philo->id_philo);
	ret_mutex2 = pthread_mutex_lock (&philo->mutex_fourchette);
	printf("philo %d prend sa fourchette \n", philo->id_philo);
	if (ret_mutex1 || ret_mutex2)
		return (1);
	if (time_to_die(philo) == -1 || check_state(philo) == 0)
		return (-1);
	gettimeofday(&philo->time.time_meal_start, NULL);
	printf("%ld philo %d eat\n", (unsigned long) \
	((1000 * philo->time.time_meal_start.tv_sec) + \
	0.001 * (philo->time.time_meal_start.tv_usec)), philo->id_philo);
	philo->nbr_of_times_philo_must_eat -= 1;
	check_if_all_philo_eat(philo);
	gettimeofday(&philo->time.time_die_start, NULL);
	usleep((philo->time_to_eat * 1000));
	return (0);
}

int	time_to_sleep(t_philo *philo)
{
	int	ret_mutex1;
	int	ret_mutex2;

	gettimeofday(&philo->time.time_meal_end, NULL);
	philo->time.timer = time_diff(&philo->time.time_meal_start, \
	&philo->time.time_meal_end);
	ret_mutex2 = pthread_mutex_unlock (philo->left);
	ret_mutex1 = pthread_mutex_unlock (&philo->mutex_fourchette);
	printf("%ld philo %d lache la fourchette\n", (unsigned long) \
	((1000 * philo->time.time_meal_end.tv_sec) + 0.001 * \
	(philo->time.time_meal_end.tv_usec)), philo->id_philo);
	if (time_to_die(philo) == -1 || check_state(philo) == 0)
		return (-1);
	gettimeofday(&philo->time.time_sleep_start, NULL);
	printf("%ld philo %d sleep\n", (unsigned long) \
	((1000 * philo->time.time_sleep_start.tv_sec) + 0.001 * \
	(philo->time.time_sleep_start.tv_usec)), philo->id_philo);
	usleep((philo->time_to_sleep * 1000));
	if (ret_mutex1 || ret_mutex2)
		return (1);
	return (0);
}

int	time_to_think(t_philo *philo)
{	
	if (time_to_die(philo) == -1 || check_state(philo) == 0)
		return (-1);
	gettimeofday(&philo->time.time_sleep_end, NULL);
	philo->time.timer = time_diff(&philo->time.time_sleep_start, \
	&philo->time.time_sleep_end);
	printf("%ld philo %d think\n", (unsigned long) \
	((1000 * philo->time.time_sleep_end.tv_sec) + 0.001 * \
	(philo->time.time_sleep_end.tv_usec)), philo->id_philo);
	return (0);
}

int	time_to_die(t_philo *philo)
{
	gettimeofday(&philo->time.time_die_end, NULL);
	philo->time.timer = time_diff(&philo->time.time_die_start, \
	&philo->time.time_die_end);
	if (philo->time.timer >= philo->time_to_die)
	{
		printf("%ld philo %d die\n", (unsigned long) \
		((1000 * philo->time.time_die_end.tv_sec) + 0.001 * \
		(philo->time.time_die_end.tv_usec)), philo->id_philo);
		philo->state = 1;
		return (-1);
	}
	return (0);
}
