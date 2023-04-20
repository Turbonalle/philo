/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:57:19 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/20 18:00:05 by jbagger          ###   ########.fr       */
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
		data->n_eat = atoi(av[1]);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!(data->philo))
		error("Malloc failed\n", data, 8);
	return (data->error);
}



pthread_mutex_t	*init_mutex(int n, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}



void	init_philo(t_data *data)
{
	int i;
	
	i = -1;
	while (++i < data->n_philo)
	{
		// usleep?
		data->philo[i].data = data;
		data->philo[i].alive = 1;
		data->philo[i].i = i + 1;
		data->philo[i].t_last_eat = 0;
		if (pthread_create(&(data->philo[i].thread), NULL, &philosopher, &(data->philo[i])) != 0)
			error("Failed to create thread\n", data, 9);
	}
}