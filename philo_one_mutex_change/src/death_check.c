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

//-----------------------------------------------------------------[DONE]

// Lock game_mutex

int	is_philosopher_dead(t_philo *p)
{
	long int	current_time;

	pthread_mutex_lock(&(p->data->game_mutex));
	current_time = time_now();
	if (current_time - p->t_last_eat > p->data->t_die)
	{
		if (data->color == ON)
			death_message(&p, RED"died"WHITE);
			printf("%-6ld %d "RED"died"WHITE"\n", current_time, p->n + 1);
		else
			printf("%-6ld %d died\n", current_time, p->n + 1);
		p->data->all_alive = DEAD;
		pthread_mutex_unlock(&(p->data->game_mutex));
		return (DEAD);
	}
	pthread_mutex_unlock(&(p->data->game_mutex));
	return (ALIVE);
}

//-----------------------------------------------------------------[DONE]

// Lock philo mutex
// Lock game mutex (in is_philosopher_dead)

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
		finished_philos = 0;
		while (++i < data->n_philo)
		{
			pthread_mutex_lock(&(data->philo[i].p_mutex));
			all_alive = is_philosopher_dead(data, i);
			if (data->philo[i].finished)
				finished_philos++;
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