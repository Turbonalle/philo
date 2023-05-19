/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:52:32 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/19 17:34:26 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	everyone_is_alive(t_philo *p)
{
	int	all_alive;

	pthread_mutex_lock(&(p->data->game_mutex));
	all_alive = p->data->all_alive;
	pthread_mutex_unlock(&(p->data->game_mutex));
	return (all_alive);
}

int		i_am_dead(t_philo *p)
{
	return (time_since(p->t_last_eat) > p->data->t_die);
}

int	is_philosopher_dead(t_data *data, int i)
{
	long int	time_since_meal;

	pthread_mutex_lock(&(data->philo[i].p_mutex));
	pthread_mutex_lock(&(data->game_mutex));
	time_since_meal = time_since(data->philo[i].t_last_eat);
	if (time_since_meal > data->t_die)
	{
		data->all_alive = DEAD;
		usleep(1000);
		if (data->color == ON)
			death_message(&(data->philo[i]), RED"died"WHITE);
		else
			death_message(&(data->philo[i]), "died");
		pthread_mutex_unlock(&(data->game_mutex));
		pthread_mutex_unlock(&(data->philo[i].p_mutex));
		return (DEAD);
	}
	pthread_mutex_unlock(&(data->game_mutex));
	pthread_mutex_unlock(&(data->philo[i].p_mutex));
	return (ALIVE);
}

void	check_finished_philosophers(t_data *data)
{
	int	finished_philos;
	int	i;

	finished_philos = 0;
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&(data->game_mutex));
		if (data->philo[i].times_eaten >= data->n_eat)
		{
			finished_philos++;
			pthread_mutex_unlock(&(data->game_mutex));
		}
		else
		{
			pthread_mutex_unlock(&(data->game_mutex));
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

	all_alive = 1;
	while (all_alive)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			all_alive = is_philosopher_dead(data, i);
			if (!all_alive)
				return ;
			usleep(10);
		}
		check_finished_philosophers(data);
		if (data->all_finished)
			return ;
		usleep(2000);
	}
}