/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:18:22 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/08 14:10:11 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	join_threads(t_data *data, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			error("Failed to join thread\n", data, 10);
		pthread_mutex_destroy(&(data->philo[i].m_start));
		pthread_mutex_destroy(&(data->philo[i].m_all_alive));
		pthread_mutex_destroy(&(data->philo[i].m_last_eat));
		pthread_mutex_destroy(&(data->philo[i].m_times_eaten));
	}
	free(data->philo);
	return (0);
}

void	destroy_forks(t_data *data, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->m_all_alive));
	free(data->forks);
}
