/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:55:22 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/20 17:58:06 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define WHITE "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"

typedef struct s_philo
{
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_t		thread;
	struct s_data	*data;
	long int		t_last_eat;
	int				times_eaten;
	int				finished;
	int				alive;
	int				i;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	t_philo			*philo;
	long int		t_start;
	int				error;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
}					t_data;

// ERROR
void			error(char *str, t_data *data, int error_code);
int				error_check(t_data *data, int ac, char *av[]);

// INIT
pthread_mutex_t	*init_mutex(int n, pthread_mutex_t *forks);
int				init_data(t_data *data, int ac, char *av[]);
void			init_philo(t_data *data);

// PHILO
void			*philosopher(void *philo);

// CLEAN
int				join_threads(t_data *data, pthread_t *philos);
void			destroy_mutex(t_data *data, pthread_mutex_t *forks);

// TIME
int				start_time(t_data *data);
long long		timestamp(void);

#endif