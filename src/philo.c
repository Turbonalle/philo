/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:34 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/20 17:54:27 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	p_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->data->forks[p->i - 1]));
	printf("%llu %d has taken a fork\n", time_since(p->data->t_start), p->i);
	pthread_mutex_lock(&(p->data->forks[(p->i - 1) % p->data->n_philo]));
	printf("%llu %d has taken a fork\n", time_since(p->data->t_start), p->i);
	printf("%llu %d is eating\n", time_since(p->data->t_start), p->i);
	p->t_last_eat = time_now();
	pthread_mutex_unlock(&(p->data->forks[p->i - 1]));
	pthread_mutex_unlock(&(p->data->forks[(p->i - 1) % p->data->n_philo]));
	printf("%llu %d has eaten %d times\n", time_since(p->data->t_start), p->i, p->times_eaten);	// Remove
	p->times_eaten++;
	if (p->times_eaten == p->data->n_eat)
		p->finished = 1;
}



void	p_sleep(t_philo *p)
{
	printf("%llu %d is sleeping\n", time_since(p->data->t_start), p->i);
	usleep(p->data->t_sleep);
}



void	p_think(t_philo *p)
{
	printf("%llu %d is thinking\n", time_since(p->data->t_start), p->i);
}



void	even_philos_wait(t_philo *p)
{
	if (p->i % 2 == 0)
		usleep(p->data->t_eat);
}



void *philosopher(void *philo)
{
	t_philo	*p;

	p = (t_philo*)philo;
	even_philos_wait(p);
	printf("I am philosopher #%d\n", p->i);
	while (p->alive)
	{
		// usleep(1000);
		p_eat(p);
		if (p->finished)
		{
			printf("%llu %d has finished\n", time_since(p->data->t_start), p->i);	// Remove
			break ;
		}
		p_sleep(p);
		p_think(p);
		if (time_since(p->t_last_eat) >= p->data->t_die)
			p->alive = 0;
	}
	return (NULL);
}