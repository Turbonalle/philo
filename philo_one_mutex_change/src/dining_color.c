/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:37:59 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/24 13:40:50 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	grab_forks_color(t_philo *p)
{
	pthread_mutex_lock(&(p->data->forks[p->left_fork]));
	if (!message(p, PURPLE"has taken a fork"WHITE))
	{
		put_down_forks(p, 1);
		return (DEAD);
	}
	pthread_mutex_lock(&(p->data->forks[p->right_fork]));
	if (!message(p, PURPLE"has taken a fork"WHITE))
	{
		put_down_forks(p, 2);
		return (DEAD);
	}
	return (ALIVE);
}

int	eat_color(t_philo *p)
{
	if (!grab_forks_color(p))
		return (DEAD);
	if (!message(p, GREEN"is eating"WHITE))
	{
		put_down_forks(p, 2);
		return (DEAD);
	}
	pthread_mutex_lock(&(p->p_mutex));
	p->t_last_eat = time_now();
	pthread_mutex_unlock(&(p->p_mutex));
	p->times_eaten++;
	if (p->times_eaten == p->data->n_eat)
	{
		pthread_mutex_lock(&(p->data->game_mutex));
		p->data->finished_philos++;
		pthread_mutex_unlock(&(p->data->game_mutex));
		put_down_forks(p, 2);
		return (DEAD);
	}
	ft_sleep(p->data->t_eat);
	put_down_forks(p, 2);
	return (ALIVE);
}

void	start_dining_color(t_philo *p)
{
	pthread_mutex_lock(&(p->data->game_mutex));
	pthread_mutex_unlock(&(p->data->game_mutex));
	if (p->data->n_philo == 1)
		starve_to_death(p);
	else
	{
		if (!message(p, YELLOW"is thinking"WHITE))
			return ;
		if (p->n % 2 == 1)
			usleep(p->data->t_eat * 1000);
		while (1)
		{
			if (!eat_color(p))
				return ;
			if (!message(p, CYAN"is sleeping"WHITE))
				return ;
			ft_sleep(p->data->t_sleep);
			if (!message(p, YELLOW"is thinking"WHITE))
				return ;
		}
	}	
}
