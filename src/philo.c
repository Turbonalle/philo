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

int	alive(t_philo *p)
{
	return (p->alive);
}

void	p_eat(t_philo *p)
{
	pick_fork_l();
	pick_fork_r();
	printf("%d #%d is Eating\n", timestamp() - p->data->t_start, p->i);
	p->t_last_eat = timestamp();
}



void	p_sleep(t_philo *p)
{
	printf("%llu %d is sleeping\n", timestamp() - p->data->t_start, p->i);
	usleep(p->data->t_sleep);
}



void *philosopher(void *philo)
{
	t_philo	*p;

	p = (t_philo*)philo;
	if (p->i % 2 == 0)
		usleep(p->data->t_eat);
	printf("I am philosopher #%d\n", p->i);
	while (p->alive)
	{
		usleep(1000);
		p_eat(p);
		if (p->data->finished)
			break ;
		p_sleep(p);
		p_think();
		if (timestamp() - p->t_last_eat >= p->data->t_die)
			p->alive = 0;
	}

	return (NULL);
}