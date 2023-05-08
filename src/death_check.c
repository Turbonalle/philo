/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:52:32 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/08 14:21:24 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	is_philosopher_dead(t_data *data, int i)
{
	int	j;

	pthread_mutex_lock(&(data->philo[i].m_last_eat));
	if (time_since(data->philo[i].t_last_eat) > data->t_die)
	{
		if (data->color == ON)
			message(&(data->philo[i]), RED"died"WHITE);
		else
			message(&(data->philo[i]), "died");
		j = -1;
		while (++j < data->n_philo)
		{
			pthread_mutex_lock(&(data->philo[j].m_all_alive));
			data->philo[j].all_alive = 0;
			pthread_mutex_unlock(&(data->philo[j].m_all_alive));
		}
		pthread_mutex_lock(&(data->m_all_alive));
		data->all_alive = 0;
		pthread_mutex_unlock(&(data->m_all_alive));
	}
	pthread_mutex_unlock(&(data->philo[i].m_last_eat));
}

void	check_finished_philosophers(t_data *data)
{
	int	finished_philos;
	int	i;

	finished_philos = 0;
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&(data->philo[i].m_times_eaten));
		if (data->philo[i].times_eaten >= data->n_eat)
		{
			finished_philos++;
			pthread_mutex_unlock(&(data->philo[i].m_times_eaten));
		}
		else
		{
			pthread_mutex_unlock(&(data->philo[i].m_times_eaten));
			break ;
		}
	}
	if (finished_philos == data->n_philo)
		data->all_finished = 1;
}

void	check_death(t_data *data)
{
	int	i;

	while (!(data->all_finished))
	{
		i = -1;
		while (++i < data->n_philo && data->all_alive)
			is_philosopher_dead(data, i);
		usleep(2000);
		if (!(data->all_alive))
			break ;
		check_finished_philosophers(data);
	}
}
