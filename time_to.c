/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:38:12 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/06 21:00:49 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_eat(philo_t *philo)
{
	int	ret_mutex1;
	int	ret_mutex2;

	
	ret_mutex1 = pthread_mutex_lock (philo->left);
	printf("philo %d prend la fourchette de gauche\n" ,philo->id_philo);
	ret_mutex2 = pthread_mutex_lock (&philo->mutex_fourchette);
	printf("philo %d prend sa fourchette \n", philo->id_philo);
	if (ret_mutex1 || ret_mutex2)
		return ;
	gettimeofday(&philo->time.time_meal_start, NULL);
	printf(" %ld philo %d mange\n",(unsigned long)((1000 * philo->time.time_meal_start.tv_sec) + 0.001 * (philo->time.time_meal_start.tv_usec)) ,philo->id_philo);
	gettimeofday(&philo->time.time_die_start, NULL);
	usleep((philo->time_to_eat * 1000));
	time_to_die(philo);
}

void	time_to_sleep(philo_t *philo)
{
	int	ret_mutex1;
	int	ret_mutex2;
	gettimeofday(&philo->time.time_meal_end, NULL);
	philo->time.timer = time_diff(&philo->time.time_meal_start, &philo->time.time_meal_end);
	printf("time to eat %d\n", philo->time_to_eat);
	ret_mutex2 = pthread_mutex_unlock (philo->left);
	ret_mutex1 = pthread_mutex_unlock (&philo->mutex_fourchette);
	printf("%ld philo %d lache la fourchette\n", (unsigned long)((1000 * philo->time.time_meal_end.tv_sec) + 0.001 * (philo->time.time_meal_end.tv_usec)),philo->id_philo);
	gettimeofday(&philo->time.time_sleep_start,NULL);
	printf("%ld philo %d dors\n", (unsigned long)((1000 * philo->time.time_sleep_start.tv_sec) + 0.001 * (philo->time.time_sleep_start.tv_usec)),philo->id_philo);
	usleep((philo->time_to_sleep * 1000));
	if (ret_mutex1 || ret_mutex2)
		return ;
	time_to_die(philo);
}

void	time_to_think(philo_t *philo)
{
	gettimeofday(&philo->time.time_sleep_end,NULL);
	//usleep((philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep)) * 1000);
	philo->time.timer = time_diff(&philo->time.time_sleep_start, &philo->time.time_sleep_end);
	printf("%ld philo %d pense\n",(unsigned long)((1000 * philo->time.time_sleep_end.tv_sec) + 0.001 * (philo->time.time_sleep_end.tv_usec)) , philo->id_philo);
	time_to_die(philo);
}

void	time_to_die(philo_t *philo)
{
	gettimeofday(&philo->time.time_die_end, NULL);
	philo->time.timer = time_diff(&philo->time.time_meal_start, &philo->time.time_die_end);
	if (philo->time.timer >= philo->time_to_die)
	{
		printf("%ld philo %d meurt\n",(unsigned long)((1000 * philo->time.time_die_end.tv_sec) + 0.001 * (philo->time.time_die_end.tv_usec)),philo->id_philo);
		exit(0);
	}
}