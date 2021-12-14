/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:56:31 by adegadri          #+#    #+#             */
/*   Updated: 2021/12/14 20:21:45 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_diner
{
	pthread_mutex_t		check_stop;
	struct timeval		start;
	struct timeval		end;
	unsigned int		timer;
	t_fork				*forks;
	struct timeval		time_print;
	struct timeval		time_all;
	struct timeval		time_die_start;
	struct timeval		time_die_end;
	struct timeval		time_meal_start;
	struct timeval		time_meal_end;
	struct timeval		time_sleep_start;
	struct timeval		time_sleep_end;
	int					philo_nb;

}	t_diner;

typedef struct s_philo
{
	pthread_mutex_t		mutex_fourchette;
	pthread_mutex_t		mutex_init;
	pthread_t			thread_philo;
	pthread_mutex_t		time_eat;
	pthread_mutex_t		time_write;
	pthread_mutex_t		*mutex_eat_dead;
	pthread_mutex_t		philo_state;
	pthread_mutex_t		*left;
	t_diner				time;
	int					state;
	int					if_ac;
	int					id_philo;
	int					nbr_of_philo;	
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		time_to_die;
	int					nbr_of_times_philo_must_eat;
}	t_philo;

typedef struct s_stock
{
	pthread_t	thread_fourchette;
	t_philo		*philo;
	t_fork		*fourchette;
	int			stock;
	int			nb_philo;
}	t_stock;

unsigned int	ft_atoi(char *str);
void			ft_putchar(char c);
void			ft_putnbr(long long n);
int				time_to_eat(t_philo *philo);
int				ft_malloc_all(t_stock *stock);
int				time_to_sleep(t_philo *philo);
int				time_to_think(t_philo *philo);
int				init_timer(t_stock *stock, int ac, char **av);
unsigned int	time_diff(struct timeval *start, struct timeval *end);
int				time_to_die(t_philo *philo);
int				if_all_philo_eat(t_philo *philo);
void			init_left_right(t_stock *stock);
int				check_if_all_philo_eat(t_philo *philo);
int				check_state(t_philo *philo);
int				init_mutex(t_stock *stock);
int				ft_sleep(t_philo *philo, int time_of_sleep);
int				ft_strlen(char *str);
int				if_not_modulo2(t_philo *philo);
int				if_modulo2(t_philo *philo);
void			ft_putstr(char *str);
void			init_all(t_stock *stock, int ac, char **av);
int				if_print(t_philo *philo, char *str);
int				when_take_fork(t_philo *philo);
void			ft_free_all(t_stock *stock);
int				only_1(t_philo *philo);
#endif