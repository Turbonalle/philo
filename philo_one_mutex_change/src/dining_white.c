/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_white.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:36:35 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/17 17:30:12 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

// void	eat_white(t_philo *p)
// {
// 	pthread_mutex_lock(&(p->data->forks[p->left_fork]));
// 	message(p, "has taken a fork");
// 	pthread_mutex_lock(&(p->data->forks[p->right_fork]));
// 	message(p, "has taken a fork");
// 	pthread_mutex_lock(&(p->m_last_eat));
// 	message(p, "is eating");
// 	p->t_last_eat = time_now();
// 	pthread_mutex_unlock(&(p->m_last_eat));
// 	ft_sleep(p->data->t_eat);
// 	pthread_mutex_lock(&(p->m_times_eaten));
// 	(p->times_eaten)++;
// 	if (p->times_eaten == p->data->n_eat)
// 		p->finished = 1;
// 	pthread_mutex_unlock(&(p->m_times_eaten));
// 	pthread_mutex_unlock(&(p->data->forks[p->left_fork]));
// 	pthread_mutex_unlock(&(p->data->forks[p->right_fork]));
// }

// void	start_dining_white(t_philo *p)
// {
// 	pthread_mutex_lock(&(p->m_start));
// 	if (p->data->n_philo == 1)
// 		starve_to_death(p);
// 	else
// 	{
// 		message(p, "is thinking");
// 		if (p->n % 2 == 1)
// 			usleep(p->data->t_eat * 1000);
// 		while (everyone_is_alive(p))
// 		{
// 			eat_white(p);
// 			if (p->finished)
// 				break ;
// 			message(p, "is sleeping");
// 			ft_sleep(p->data->t_sleep);
// 			message(p, "is thinking");
// 		}
// 	}	
// 	pthread_mutex_unlock(&(p->m_start));
// }
