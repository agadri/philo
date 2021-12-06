/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:38:23 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/06 21:05:27 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Fonction pour les threads des clients. */
static void * ft_philo (void *data) //(void * p_data)
{
	philo_t	*philo = (philo_t *) data;
	pthread_mutex_lock(&philo->mutex_init);
	pthread_mutex_unlock(&philo->mutex_init);
	printf ("fn philo ->>%d\n",philo->id_philo);
	
	while (1)
	{
		time_to_eat(philo);
		time_to_sleep(philo);
		time_to_think(philo);
	}
	return NULL;
}
 
int	ft_malloc_all(stock_t *stock)
{
	stock->stock = 6;
	stock->philo = malloc(sizeof(philo_t) * stock->nb_philo);
	if (!stock->philo)
		return (1);
	stock->fourchette = malloc(sizeof(fork_t) * stock->nb_philo);
	if (!stock->fourchette)
		return (1);
	return (0);
}

void	init_left_right(stock_t *stock)
{
	int	i;
	i = 0;
	printf ("left et right de chaque thread attribue!\n");
	while (i < stock->nb_philo)
	{
		if (i == 0) 
			stock->philo[i].left = &(stock->philo[stock->nb_philo - 1].mutex_fourchette);
		else if (i == stock->nb_philo - 1)
			stock->philo[i].left = &(stock->philo[i - 1].mutex_fourchette);//gauche
		else
			stock->philo[i].left = &(stock->philo[i - 1].mutex_fourchette);//gauche
		i++;
	}
}

int	init_timer(stock_t *stock,int ac, char **av)
{
	int	i;

	i = 0;
	stock->nb_philo = ft_atoi(av[1]);
	while (i < stock->nb_philo)
	{

		if (ac >= 5)
		{
			stock->philo[i].id_philo = i + 1;		
			
			stock->philo[i].time_to_die = ft_atoi(av[2]);
			stock->philo[i].time_to_eat = ft_atoi(av[3]);
			stock->philo[i].time_to_sleep = ft_atoi(av[4]);
		}
		i++;
	}
	return (0);
}

int main (int ac, char **av)
{

	stock_t stock;

	int i = 0;
	int ret = 0;
	if (ft_malloc_all(&stock))
		return (0);
	init_timer(&stock, ac, av);
	init_left_right(&stock);
	i = 0;
	printf ("Creation des threads philo !\n");
	while (i < stock.nb_philo)
	{
		
		ret = pthread_create (&stock.philo[i].thread_philo, NULL, &ft_philo, (void *) &(stock.philo[i]));
		printf("thread philo %d cree\n",i + 1);
		if (ret)
			printf ("Error");
		usleep(50);
		i++;
	}
	i = 0;
	while (i < stock.nb_philo)
		pthread_join (stock.philo[i++].thread_philo, NULL);
	return EXIT_SUCCESS;
}