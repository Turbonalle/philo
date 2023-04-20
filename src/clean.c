/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:18:22 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/20 17:57:43 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	join_threads(t_data *data, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(philos[i], NULL) != 0)
			error("Failed to join thread\n", data, 10);
		i++;
	}
	return (0);
}

void	destroy_mutex(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}