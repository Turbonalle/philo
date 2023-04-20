/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:36:37 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/20 15:39:21 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	start_time(t_data *data)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL))
	{
		error("gettimeofday() failed\n", data, 8);
		return (data->error);
	}
	data->t_start = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (0);
}

long long	timestamp(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}