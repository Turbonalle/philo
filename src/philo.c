/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:34 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/27 14:06:29 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	ft_sleep(int ms)
{
	long int	time;

	time = time_now();
	while (time_now() - time < ms)
		usleep(50);
}



void	p_eat(t_philo *p)
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



void	p_sleep(t_philo *p)
{
	message(p, CYAN"is sleeping"WHITE);
	ft_sleep(p->data->t_sleep);
}



void	p_think(t_philo *p)
{
	message(p, YELLOW"is thinking"WHITE);
}


int	alive(t_philo *p)
{
	int all_alive;
	
	pthread_mutex_lock(&(p->data->m_death));
	all_alive = p->data->all_alive;
	pthread_mutex_unlock(&(p->data->m_death));
	return (all_alive);
}

int	everyone_is_alive(t_philo *p)
{
	int all_alive;
	
	pthread_mutex_lock(&(p->m_all_alive));
	all_alive = p->all_alive;
	pthread_mutex_unlock(&(p->m_all_alive));
	return (all_alive);
}

void	starve_to_death(t_philo *p)
{
	// message(p, YELLOW"is all alone"WHITE);
	pthread_mutex_lock(&(p->data->forks[p->left_fork]));
	message(p, PURPLE"has taken a fork"WHITE);
	while (alive(p))
		usleep(50);
	pthread_mutex_unlock(&(p->data->forks[p->left_fork]));
}


void *philosopher(void *philo)
{
	t_philo	*p;
	p = (t_philo*)philo;
	
	if (p->data->n_philo == 1)
		starve_to_death(p);
	else
	{
		if (p->n % 2 == 0)
			usleep(p->data->t_eat * 1000);
		while (everyone_is_alive(p))
		{
			p_eat(p);
			if (p->finished)
				break ;
			p_sleep(p);
			p_think(p);
		}
	}	
	return (NULL);
}