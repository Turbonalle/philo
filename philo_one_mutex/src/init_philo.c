/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:10:23 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/18 12:43:57 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

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

int	init_philo(t_data *data)
{
	int	i;

	data->all_alive = 1;
	data->all_finished = 0;
	i = -1;
	pthread_mutex_lock(&(data->game_mutex));
	while (++i < data->n_philo)
	{
		init_philo_data(data, i);
		if (pthread_mutex_init(&data->philo[i].p_mutex, NULL) != 0)
		{
			destroy_forks(data, i + 1);
			error("Failed initializing mutex\n", data, 10);
			return (data->error);
		}
		if (pthread_create(&(data->philo[i].thread),
				NULL, &philosopher, &(data->philo[i])) != 0)
		{
			error("Failed to create thread\n", data, 9);
			join_threads(data, i + 1);
			destroy_forks(data, data->n_philo);
			return (data->error);
		}
	}
	start_time(data);
	// printf("data.start = %lu\n", data->t_start);
	i = -1;
	while (++i < data->n_philo)
		data->philo[i].t_last_eat = data->t_start;
	pthread_mutex_unlock(&(data->game_mutex));
	return (data->error);
}
