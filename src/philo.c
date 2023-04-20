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
	printf("#%d is Eating\n", p->i);
}

void *philosopher(void *philo)
{
	t_philo	*p;

	p = (t_philo*)philo;
	printf("I am philosopher #%d\n", p->i);
	while (p->alive)
	{
		usleep(1000);
		p_eat(p);
		// p_sleep();
		// p_think();
		
	}

	return (NULL);
}