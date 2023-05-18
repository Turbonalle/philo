/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:36:37 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/18 10:43:14 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	start_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
	{
		error("gettimeofday() failed\n", data, 10);
		return (data->error);
	}
	data->t_start = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (0);
}

long int	time_since(long int start)
{
	return (time_now() - start);
}

long int	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
