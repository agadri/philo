/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:38:23 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/07 20:01:53 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	gettimeofday(&philo->time.time_die_start, NULL);
	pthread_mutex_lock(&philo->mutex_init);
	pthread_mutex_unlock(&philo->mutex_init);
	while (1)
	{
		if (time_to_die(philo) == -1 || check_state(philo) == 0 || \
		(time_to_eat(philo) != 0) || (time_to_sleep(philo) != 0) \
		|| (time_to_think(philo) != 0))
		{
			pthread_mutex_unlock (philo->left);
			pthread_mutex_unlock (&philo->mutex_fourchette);
			return (NULL);
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_stock	stock;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (ft_malloc_all(&stock))
		return (1);
	init_timer(&stock, ac, av);
	init_left_right(&stock);
	i = 0;
	while (i < stock.nb_philo)
	{
		ret = pthread_create (&stock.philo[i].thread_philo, NULL, \
		&ft_philo, (void *) &(stock.philo[i]));
		if (ret)
			return (1);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < stock.nb_philo)
		pthread_join (stock.philo[i++].thread_philo, NULL);
	return (EXIT_SUCCESS);
}
