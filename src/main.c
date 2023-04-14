/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:45 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/14 16:03:33 by jbagger          ###   ########.fr       */
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



int	init_data(t_data *data, int ac, char *av[])
{
	data->philo = atoi(av[1]);
	data->die = atoi(av[2]);
	data->eat = atoi(av[3]);
	data->sleep = atoi(av[4]);
	if (ac == 6)
		data->times_to_eat = atoi(av[1]);
	return (0);
}

void *philosopher(void *arg)
{
	t_data *d;

	d = (t_data*)arg;
	printf("We have %d philosophers\n", d->philo);

	/*
	
	Here we create eat, sleep, repeat and mutex stuff
	.
	.
	.
	.
	.

	*/

	return (NULL);
}

int	start_dining(t_data *data)
{
	struct timeval	start_time;
	pthread_t 		philos[data->philo];
	int				i;

	if (gettimeofday(&start_time, NULL))
	{
		error("gettimeofday() failed\n", data, 8);
		return (data->error);
	}
	data->start = start_time.tv_sec * 1000000 + start_time.tv_usec;
	i = 0;
	while (i < data->philo)
	{
		// usleep?
		if (pthread_create(&philos[i], NULL, &philosopher, data) != 0)
			error("Failed to create thread", data, 9);
		i++;
	}
	i = 0;
	while (i < data->philo)
	{
		if (pthread_join(philos[i], NULL) != 0)
			error("Failed to join thread", data, 10);
		i++;
	}
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