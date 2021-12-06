#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct s_fork {
	
	pthread_mutex_t mutex;

}	fork_t;

typedef struct s_diner {
	
	pthread_mutex_t		check_stop;
	struct	timeval 	start;
	struct	timeval 	end;
	float					timer;
	fork_t				*forks;
	int					philo_nb;

	////////////////////
	struct	timeval		time_die_start;
	struct	timeval		time_die_end;
	struct	timeval		time_meal_start;
	struct	timeval		time_meal_end;
	struct	timeval		time_sleep_start;
	struct	timeval		time_sleep_end;
	

}	diner_t;

typedef struct s_philo {
	pthread_mutex_t 	mutex_fourchette;
	pthread_mutex_t		mutex_init;
	pthread_t			thread_philo;
	pthread_mutex_t		*left;
	diner_t				time;
	int 				id_philo;	
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					number_of_times_each_philosopher_must_eat;

}	philo_t;




typedef struct s_stock // sert de mutex
{
	pthread_t thread_fourchette;
	
	philo_t *philo;
	fork_t	*fourchette;
	int	stock;
	int	nb_philo;


}	stock_t;

int		ft_atoi(char *str);
void	time_to_eat(philo_t *philo);
void	time_to_sleep(philo_t *philo);
void	time_to_think(philo_t *philo);
float	time_diff(struct timeval *start, struct timeval *end);
void	time_to_die(philo_t *philo);
int		if_all_philo_eat(philo_t *philo);

#endif