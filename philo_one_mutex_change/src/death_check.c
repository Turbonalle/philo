/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:52:32 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/24 13:26:25 by jbagger          ###   ########.fr       */
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

int	i_am_dead(t_philo *p)
{
	return (time_since(p->t_last_eat) > p->data->t_die);
}

int	is_philosopher_dead(t_philo *p)
{
	long int	current_time;

	pthread_mutex_lock(&(p->data->game_mutex));
	current_time = time_now();
	if (current_time - p->t_last_eat > p->data->t_die)
	{
		printf("%-6ld %d ", current_time - p->data->t_start, p->n + 1);
		if (p->data->color == ON)
			printf(RED"died"WHITE"\n");
		else
			printf("died");
		p->data->all_alive = DEAD;
		pthread_mutex_unlock(&(p->data->game_mutex));
		return (DEAD);
	}
	pthread_mutex_unlock(&(p->data->game_mutex));
	return (ALIVE);
}

void	check_death(t_data *data)
{
	int	all_alive;
	int	finished_philos;
	int	i;

	all_alive = 1;
	finished_philos = 0;
	while (all_alive && finished_philos < data->n_philo)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			pthread_mutex_lock(&(data->philo[i].p_mutex));
			all_alive = is_philosopher_dead(&(data->philo[i]));
			pthread_mutex_lock(&(data->game_mutex));
			finished_philos = data->finished_philos;
			pthread_mutex_unlock(&(data->game_mutex));
			if (!all_alive || finished_philos >= data->n_philo)
			{
				pthread_mutex_unlock(&(data->philo[i].p_mutex));
				return ;
			}
			pthread_mutex_unlock(&(data->philo[i].p_mutex));
		}
		usleep(2000);
	}
}
