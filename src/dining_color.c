/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:37:59 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/08 10:43:47 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	eat_color(t_philo *p)
{
	pthread_mutex_lock(&(p->data->forks[p->left_fork]));
	message(p, PURPLE"has taken a fork"WHITE);
	pthread_mutex_lock(&(p->data->forks[p->right_fork]));
	message(p, PURPLE"has taken a fork"WHITE);
	pthread_mutex_lock(&(p->m_last_eat));
	message(p, GREEN"is eating"WHITE);
	p->t_last_eat = time_now();
	pthread_mutex_unlock(&(p->m_last_eat));
	ft_sleep(p->data->t_eat);
	pthread_mutex_lock(&(p->m_times_eaten));
	(p->times_eaten)++;
	if (p->times_eaten == p->data->n_eat)
		p->finished = 1;
	pthread_mutex_unlock(&(p->m_times_eaten));
	pthread_mutex_unlock(&(p->data->forks[p->left_fork]));
	pthread_mutex_unlock(&(p->data->forks[p->right_fork]));
}

void	start_dining_color(t_philo *p)
{
	pthread_mutex_lock(&(p->m_start));
	if (p->data->n_philo == 1)
		starve_to_death(p);
	else
	{
		if (p->n % 2 == 1)
			usleep(p->data->t_eat * 1000);
		while (everyone_is_alive(p))
		{
			eat_color(p);
			if (p->finished)
				break ;
			message(p, CYAN"is sleeping"WHITE);
			ft_sleep(p->data->t_sleep);
			message(p, YELLOW"is thinking"WHITE);
		}
	}	
	pthread_mutex_unlock(&(p->m_start));
}
