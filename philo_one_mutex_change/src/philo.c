/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:59:34 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/24 13:49:00 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	put_down_forks(t_philo *p, int forks)
{
	if (forks == 1)
		pthread_mutex_unlock(&(p->data->forks[p->left_fork]));
	if (forks == 2)
	{
		pthread_mutex_unlock(&(p->data->forks[p->left_fork]));
		pthread_mutex_unlock(&(p->data->forks[p->right_fork]));
	}
}

void	ft_sleep(int ms)
{
	long int	start;

	start = time_now();
	while (time_since(start) < ms)
		usleep(2000);
}

void	starve_to_death(t_philo *p)
{
	pthread_mutex_lock(&(p->data->forks[p->left_fork]));
	if (p->data->color == ON)
		message(p, RED"has taken a fork"WHITE);
	else
		message(p, "has taken a fork");
	while (time_since(p->data->t_start) < p->data->t_die)
		usleep(50);
	pthread_mutex_unlock(&(p->data->forks[p->left_fork]));
}

void	*philosopher(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->data->color == ON)
		start_dining_color(p);
	else
		start_dining_white(p);
	return (NULL);
}
