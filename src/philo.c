/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:34 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/25 12:35:53 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	ft_sleep(int ms)
{
	long int	time;

	time = time_now();
	while (time_now() - time < ms)
		usleep(10);
}

void	pick_first_fork(t_philo *p)
{
	pthread_mutex_lock(&(p->data->m_death));
	if (p->data->all_alive)
	{
		pthread_mutex_lock(&(p->data->forks[p->fork1]));
		message(p, CYAN"has taken a fork"WHITE);
	}
	pthread_mutex_unlock(&(p->data->m_death));
}

void	pick_second_fork(t_philo *p)
{
	pthread_mutex_lock(&(p->data->m_death));
	if (p->data->all_alive)
	{
		pthread_mutex_lock(&(p->data->forks[p->fork2]));
		message(p, CYAN"has taken a fork"WHITE);
	}
	pthread_mutex_unlock(&(p->data->m_death));
}

void	p_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->data->m_death));
	if (p->data->all_alive)
	{
		message(p, YELLOW"is eating"WHITE);
	}
	pthread_mutex_unlock(&(p->data->m_death));
	p->t_last_eat = time_now();
	usleep(p->data->t_eat * 1000);
	p->times_eaten++;
	if (p->times_eaten == p->data->n_eat)
		p->finished = 1;
}

void	put_forks_down(t_philo *p)
{
	pthread_mutex_unlock(&(p->data->forks[p->fork1]));
	pthread_mutex_unlock(&(p->data->forks[p->fork2]));
}


void	p_sleep(t_philo *p)
{
	pthread_mutex_lock(&(p->data->m_death));
	if (p->data->all_alive)
	{
		message(p, "is sleeping"WHITE);
	}
	pthread_mutex_unlock(&(p->data->m_death));
	ft_sleep(p->data->t_sleep);
}



void	p_think(t_philo *p)
{
	pthread_mutex_lock(&(p->data->m_death));
	if (p->data->all_alive)
	{
		message(p, "is thinking"WHITE);
	}
	pthread_mutex_unlock(&(p->data->m_death));
}



void	even_philos_wait(t_philo *p)
{
	int	extra_time;

	extra_time = 50;
	if (p->n % 2 == 0)
		usleep(p->data->t_eat + extra_time);
}


int	alive(t_philo *p)
{
	int	alive;
	pthread_mutex_lock(&(p->data->m_death));
	alive = p->data->all_alive;
	pthread_mutex_unlock(&(p->data->m_death));
	return (alive);
}


void *philosopher(void *philo)
{
	t_philo	*p;

	p = (t_philo*)philo;
	even_philos_wait(p);
	while (alive(p))
	{
		pick_first_fork(p);
		pick_second_fork(p);
		p_eat(p);
		put_forks_down(p);
		if (p->finished)
			break ;
		p_sleep(p);
		p_think(p);
	}
	return (NULL);
}