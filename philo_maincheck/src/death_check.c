/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:52:32 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/09 14:25:07 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"


// ---- RETURN DEATH INFO ------------------------------------------------------

int	everyone_is_alive(t_philo *p)
{
	int	all_alive;

	pthread_mutex_lock(&(p->m_all_alive));
	all_alive = p->all_alive;
	pthread_mutex_unlock(&(p->m_all_alive));
	return (all_alive);
}

int		i_am_dead(t_philo *p)
{
	return (time_since(p->t_last_eat) > p->data->t_die);
}


// ---- TELL -------------------------------------------------------------------

void	tell_main(t_philo *p)
{
	pthread_mutex_lock(&(p->data->m_all_alive));
	p->data->all_alive = 0;
	pthread_mutex_unlock(&(p->data->m_all_alive));
}

// void	tell_philos(t_philo *p)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < p->data->n_philo)
// 	{
// 		pthread_mutex_lock(&(p->data->philo[i].m_all_alive));
// 		p->data->philo[i].all_alive = 0;
// 		pthread_mutex_unlock(&(p->data->philo[i].m_all_alive));
// 	}
// }


// ---- MAIN CHECK -------------------------------------------------------------

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
	{
		printf(GREEN"ALL FINISHED!\n"WHITE);
		data->all_finished = 1;
	}
}

void	check_death(t_data *data)
{
	int	all_alive;
	int	i;

	while (!(data->all_finished))
	{
		i = -1;
		while (++i < data->n_philo)
		{
			pthread_mutex_lock(&(data->m_all_alive));
			all_alive = data->all_alive;
			pthread_mutex_unlock(&(data->m_all_alive));
			if (all_alive)
				is_philosopher_dead(data, i);
		}
		pthread_mutex_lock(&(data->m_all_alive));
		all_alive = data->all_alive;
		pthread_mutex_unlock(&(data->m_all_alive));
		if (!all_alive)
			break ;
		check_finished_philosophers(data);
		usleep(2000);
	}
}
