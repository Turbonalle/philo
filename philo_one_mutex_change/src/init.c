/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:57:19 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/24 09:42:07 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	init_data(t_data *data, int ac, char *av[])
{
	data->n_philo = atoi(av[1]);
	data->t_die = atoi(av[2]);
	data->t_eat = atoi(av[3]);
	data->t_sleep = atoi(av[4]);
	// printf("%d %d %d %d\n", data->n_philo, data->t_die, data->t_eat, data->t_sleep);
	if (ac == 6)
		data->n_eat = atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!(data->philo))
		error("Malloc failed (philo)\n", data, 8);
	return (data->error);
}

int	init_mutex(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!(forks))
		error("Malloc failed (forks)\n", data, 9);
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_forks(data, i + 1);
			error("Failed initializing mutex\n", data, 10);
			return (data->error);
		}
	}
	if (pthread_mutex_init(&(data->game_mutex), NULL) != 0)
	{
		error("Failed initializing mutex\n", data, 10);
		return (data->error);
	}
	data->forks = forks;
	return (data->error);
}
