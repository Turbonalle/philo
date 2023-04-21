/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:45 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/20 17:58:21 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/*
Arguments:
	- n philo
	- time to die
	- time to eat
	- time to sleep
	- n times each philo must eat	(optional)

Stop when:
	- a philo dies
	- n times eaten is reached

Print:
	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is sleeping
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died		(no more than 10ms after dying)


Plan:
- Pass in all info into struct
- Create forks
- Create threads
- Set starting time	(gettimeofday)



Tip:
- usleep in every while loop?

*/



int	start_dining(t_data *data)
{
	pthread_t 		philos[data->n_philo];
	pthread_mutex_t forks[data->n_philo];

	data->forks = init_mutex(data->n_philo, forks);
	start_time(data);
	init_philo(data);
	join_threads(data, philos);
	destroy_mutex(data, forks);
	return (0);
}



int main(int ac, char *av[])
{
	t_data	data;

	if (error_check(&data, ac, av))
		return (data.error);
	if (init_data(&data, ac, av))
		return (data.error);
	if (start_dining(&data))
		return (data.error);

	printf(GREEN"Success!\n");
	return (0);
}