/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:34 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/24 15:11:13 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	message(t_philo *p, char *msg)
{
	pthread_mutex_lock(&(p->data->print));
	printf("%-6llu %d %s\n", time_since(p->data->t_start), p->n, msg);
	pthread_mutex_unlock(&(p->data->print));
}

void	ft_sleep(int ms)
{
	long int	time;

	time = time_now();
	while (time_now() - time < ms)
		usleep(ms / 10);
}

int		alive(t_philo *p)
{
	if (time_since(p->t_last_eat) >= p->data->t_die)
	{
		pthread_mutex_lock(&(p->data->death));
		p->data->all_alive = 0;
		pthread_mutex_unlock(&(p->data->death));
		return (1);
	}
	return (0);
}

void	pick_first_fork(t_philo *p)
{
	pthread_mutex_lock(&(p->data->forks[p->fork1]));
	message(p, CYAN"has taken a fork"WHITE);
}

void	pick_second_fork(t_philo *p)
{
	pthread_mutex_lock(&(p->data->forks[p->fork2]));
	message(p, CYAN"has taken a fork"WHITE);
}

void	p_eat(t_philo *p)
{
	message(p, PURPLE"is eating"WHITE);
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
	message(p, YELLOW"is sleeping"WHITE);
	ft_sleep(p->data->t_sleep);
}



void	p_think(t_philo *p)
{
		message(p, "is thinking");
}



void	even_philos_wait(t_philo *p)
{
	int	extra_time;

	extra_time = 50;
	if (p->n % 2 == 0)
		usleep(p->data->t_eat + extra_time);
}



void *philosopher(void *philo)
{
	t_philo	*p;

	p = (t_philo*)philo;
	// even_philos_wait(p);
	while (p->data->all_alive)
	{
		// usleep(1000);
		if (alive(p))
		{
			message(p, RED"died"WHITE);
			break ;
		}
		pick_first_fork(p);
		if (alive(p))
		{
			pthread_mutex_unlock(&(p->data->forks[p->fork1]));
			message(p, RED"died"WHITE);
			break ;
		}
		pick_second_fork(p);
		if (alive(p))
		{
			pthread_mutex_unlock(&(p->data->forks[p->fork1]));
			pthread_mutex_unlock(&(p->data->forks[p->fork2]));
			message(p, RED"died"WHITE);
			break ;
		}
		p_eat(p);
		put_forks_down(p);
		if (p->finished)
		{
			// message(p, GREEN"HAS FINISHED"WHITE);	// Remove
			break ;
		}
		p_sleep(p);
		p_think(p);
	}
	return (NULL);
}