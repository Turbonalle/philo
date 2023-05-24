/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:55:22 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/24 13:09:24 by jbagger          ###   ########.fr       */
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
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define ON 1
# define OFF 0
# define ALIVE 1
# define DEAD 0
# define SUCCESS 1
# define FAIL 0

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	p_mutex;
	struct s_data	*data;
	long int		t_last_eat;
	int				left_fork;
	int				right_fork;
	int				times_eaten;
	int				n;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	game_mutex;
	t_philo			*philo;
	long int		t_start;
	int				error;
	int				color;
	int				all_alive;
	int				all_finished;
	int				finished_philos;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
}					t_data;

// DEATH CHECK
void		check_death(t_data *data);

// ERROR
void		error(char *str, t_data *data, int error_code);
int			error_check(t_data *data, int ac, char *av[]);

// INIT
int			init_mutex(t_data *data);
int			init_data(t_data *data, int ac, char *av[]);
int			init_philo(t_data *data);

// PHILO
void		*philosopher(void *philo);
void		ft_sleep(int ms);
int			everyone_is_alive(t_philo *p);
void		starve_to_death(t_philo *p);

// DINING
void		start_dining_color(t_philo *p);
void		start_dining_white(t_philo *p);
void		put_down_forks(t_philo *p, int forks);

// CLEAN
int			join_threads(t_data *data, int n);
void		destroy_forks(t_data *data, int n);

// TIME
int			start_time(t_data *data);
long int	time_since(long int start);
long int	time_now(void);

// UTILS
int			message(t_philo *p, char *msg);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif