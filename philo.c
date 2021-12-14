/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:38:23 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 20:30:18 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_philo(void *data)
{
	t_philo	*philo;
	int		dead_eat;

	philo = (t_philo *) data;
	pthread_mutex_lock(&philo->mutex_init);
	pthread_mutex_unlock(&philo->mutex_init);
	while (1)
	{
		if (time_to_die(philo) == -1 || check_state(philo) == 0)
			break ;
		dead_eat = time_to_eat(philo);
		if (dead_eat == -2 && \
		!pthread_mutex_unlock (&philo->mutex_fourchette))
			return (NULL);
		else if (dead_eat == -3 && \
		!pthread_mutex_unlock (philo->left))
			return (NULL);
		if (dead_eat == -1 && \
		!pthread_mutex_unlock (&philo->mutex_fourchette) && \
		!pthread_mutex_unlock (philo->left))
			return (NULL);
		if (time_to_sleep(philo) != 0 || time_to_think(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

int	thread_join(t_stock *stock)
{
	int		i;
	int		ret;
	void	*retval;

	i = 0;
	while (i < stock->nb_philo)
	{
		ret = pthread_join (stock->philo[i++].thread_philo, &retval);
		if (retval == PTHREAD_CANCELED || ret != 0)
		{
			ft_free_all(stock);
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_stock	stock;
	int		i;
	int		ret;

	if (ac < 5)
		return (1);
	i = 0;
	ret = 0;
	stock.nb_philo = ft_atoi(av[1]);
	if (ft_malloc_all(&stock))
		return (1);
	init_all(&stock, ac, av);
	i = -1;
	while (++i < stock.nb_philo)
	{
		ret = pthread_create (&stock.philo[i].thread_philo, NULL, \
		&ft_philo, (void *) &(stock.philo[i]));
		if (ret)
			return (1);
		usleep(60);
	}
	if (thread_join(&stock) == 1)
		return (1);
	ft_free_all(&stock);
	return (EXIT_SUCCESS);
}
