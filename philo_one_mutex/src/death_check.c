/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:52:32 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/18 14:52:44 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"


// ---- RETURN DEATH INFO ------------------------------------------------------

int	everyone_is_alive(t_philo *p)
{
	int	all_alive;

	pthread_mutex_lock(&(p->data->game_mutex));
	all_alive = p->all_alive;
	pthread_mutex_unlock(&(p->data->game_mutex));
	return (all_alive);
}

int		i_am_dead(t_philo *p)
{
	return (time_since(p->t_last_eat) > p->data->t_die);
}


// ---- TELL -------------------------------------------------------------------

void	tell_main(t_philo *p)
{
	pthread_mutex_lock(&(p->data->game_mutex));
	p->all_alive = 0;
	pthread_mutex_unlock(&(p->data->game_mutex));
}

void	tell_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].all_alive = 0;
	}
}


// ---- MAIN CHECK -------------------------------------------------------------

void	is_philosopher_dead(t_data *data, int i)
{
	long int	time_since_meal;

	pthread_mutex_lock(&(data->philo[i].p_mutex));
	pthread_mutex_lock(&(data->game_mutex));
	time_since_meal = time_since(data->philo[i].t_last_eat);
	if (time_since_meal > data->t_die)
	{
		tell_philos(data);
		data->all_alive = 0;
		usleep(1000);
		if (data->color == ON)
			death_message(&(data->philo[i]), RED"died"WHITE);
		else
			death_message(&(data->philo[i]), "died");
	}
	pthread_mutex_unlock(&(data->game_mutex));
	pthread_mutex_unlock(&(data->philo[i].p_mutex));
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

	while (data->all_alive)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			if (all_alive)
				is_philosopher_dead(data, i);
		}
		check_finished_philosophers(data);
		if (data->all_finished)
			return ;
		usleep(2000);
	}
}