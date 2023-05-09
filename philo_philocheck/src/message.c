/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:57:08 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/09 10:00:45 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	message(t_philo *p, char *msg)
{
	pthread_mutex_lock(&(p->data->m_all_alive));
	if (p->data->all_alive)
		printf("%-6ld %d %s\n", time_since(p->data->t_start), p->n + 1, msg);
	pthread_mutex_unlock(&(p->data->m_all_alive));
}

void	tell_main(t_philo *p)
{
	pthread_mutex_lock(&(p->data->m_all_alive));
	p->data->all_alive = 0;
	pthread_mutex_unlock(&(p->data->m_all_alive));
}

void	tell_everyone(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&(data->philo[i].m_all_alive));
		data->philo[i].all_alive = 0;
		pthread_mutex_unlock(&(data->philo[i].m_all_alive));
	}
}
