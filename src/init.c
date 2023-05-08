/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:57:19 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/08 13:21:44 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	init_data(t_data *data, int ac, char *av[])
{
	data->n_philo = atoi(av[1]);
	data->t_die = atoi(av[2]);
	data->t_eat = atoi(av[3]);
	data->t_sleep = atoi(av[4]);
	if (ac == 6)
		data->n_eat = atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!(data->philo))
		error("Malloc failed\n", data, 8);
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
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&(data->m_all_alive), NULL);
	data->forks = forks;
	return (data->error);
}
