/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:13:37 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 20:31:10 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_stock *stock)
{
	if (stock->philo->mutex_eat_dead)
		free(stock->philo->mutex_eat_dead);
	free(stock->philo);
	if (stock->fourchette)
		free(stock->fourchette);
}
