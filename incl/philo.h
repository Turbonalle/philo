/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:55:22 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/14 15:57:08 by jbagger          ###   ########.fr       */
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

typedef struct s_data
{
	int			error;
	int			philo;
	int			die;
	int			eat;
	int			sleep;
	int			times_to_eat;
	long int	start;
	long int	time;
}				t_data;

typedef struct s_philo
{
	pthread_t	*philo;
}				t_philo;

// ERROR
void	error(char *str, t_data *data, int error_code);
int		error_check(t_data *data, int ac, char *av[]);

#endif