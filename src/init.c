/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:57:19 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/27 16:11:17 by jbagger          ###   ########.fr       */
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



pthread_mutex_t *init_mutex(t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&(data->m_all_alive), NULL);
	return (forks);
}

void	init_philo_mutexes(t_data *data, int i)
{
	pthread_mutex_init(&(data->philo[i].m_all_alive), NULL);
	pthread_mutex_init(&(data->philo[i].m_last_eat), NULL);
	pthread_mutex_init(&(data->philo[i].m_times_eaten), NULL);
}

void	init_philo_data(t_data *data, int i)
{
	data->philo[i].data = data;
	data->philo[i].left_fork = i;
	data->philo[i].right_fork = (i + 1) % data->n_philo;
	data->philo[i].times_eaten = 0;
	data->philo[i].finished = 0;
	data->philo[i].all_alive = 1;
	data->philo[i].n = i;
}

void	init_philo(t_data *data)
{
	int i;
	
	data->all_alive = 1;
	data->all_finished = 0;
	start_time(data);
	i = -1;
	while (++i < data->n_philo)
	{
		init_philo_mutexes(data, i);
		init_philo_data(data, i);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].t_last_eat = data->t_start;
		if (pthread_create(&(data->philo[i].thread), NULL, &philosopher, &(data->philo[i])) != 0)
			error("Failed to create thread\n", data, 9);
	}
}