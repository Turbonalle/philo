/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:52:32 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/09 10:01:47 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	i_am_dead(t_philo *p)
{
	return (time_since(p->t_last_eat) > p->data->t_die);
}

int	everyone_is_alive(t_philo *p)
{
	int	all_alive;

	pthread_mutex_lock(&(p->m_all_alive));
	all_alive = p->all_alive;
	pthread_mutex_unlock(&(p->m_all_alive));
	return (all_alive);
}

int	all_alive(t_data *data)
{
	int	all_alive;

	pthread_mutex_lock(&(data->m_all_alive));
	all_alive = data->all_alive;
	pthread_mutex_unlock(&(data->m_all_alive));
	return (all_alive);
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
		if (!all_alive(data))
		{
			tell_everyone(data);
			break ;
		}
		check_finished_philosophers(data);
		usleep(2000);
	}
}
