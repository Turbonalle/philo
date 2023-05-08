/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:10:23 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/08 10:44:10 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	init_philo_mutexes(t_data *data, int i)
{
	pthread_mutex_init(&(data->philo[i].m_start), NULL);
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

void	let_philosophers_start(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].t_last_eat = data->t_start;
		pthread_mutex_unlock(&(data->philo[i].m_start));
	}
}

int	init_philo(t_data *data)
{
	int	i;

	data->all_alive = 1;
	data->all_finished = 0;
	i = -1;
	while (++i < data->n_philo)
	{
		init_philo_mutexes(data, i);
		init_philo_data(data, i);
		pthread_mutex_lock(&(data->philo[i].m_start));
		if (pthread_create(&(data->philo[i].thread),
				NULL, &philosopher, &(data->philo[i])) != 0)
		{
			error("Failed to create thread\n", data, 9);
			join_n_threads(data, i + 1);
			return (data->error);
		}
	}
	start_time(data);
	let_philosophers_start(data);
	return (data->error);
}
