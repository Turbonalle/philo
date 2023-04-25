/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:45 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/25 16:48:48 by jbagger          ###   ########.fr       */
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

- if (n_philo % 2 == 0)
	if (t_die >= t_eat * 2 + 10 && t_die >= t_eat + t_sleep + 10)
		->success
- if (n_philo % 2 == 1)
	if (t_die >= t_eat * 3 + 10 && t_die >= t_eat + t_sleep + 10)
		->success

*/

void	message(t_philo *p, char *msg)
{
	pthread_mutex_lock(&(p->data->m_death));
	printf("%-6llu %d %s\n", time_since(p->data->t_start), p->n, msg);
	pthread_mutex_unlock(&(p->data->m_death));
}

void	check_death(t_data *data)
{
	int	i;

	while (data->all_alive)
	{
		usleep(1000);
		i = -1;
		while (++i < data->n_philo)
		{
			if (time_since(data->philo[i].t_last_eat) >= data->t_die)
			{
				pthread_mutex_lock(&(data->m_death));
				data->all_alive = 0;
				message(&(data->philo[i]), RED"died"WHITE);
				pthread_mutex_unlock(&(data->m_death));
				break ;
			}
		}
	}
}

int	start_dining(t_data *data)
{
	pthread_mutex_t forks[data->n_philo];

	data->forks = init_mutex(data, forks);
	init_philo(data);
	check_death(data);
	join_threads(data);
	destroy_mutex(data, forks);
	return (0);
}

// int	start_dining(t_data *data)
// {
// 	init_mutex(data);
// 	init_philo(data);
// 	check_death(data);
// 	join_threads(data);
// 	destroy_mutex(data, data->forks);
// 	return (0);
// }



int main(int ac, char *av[])
{
	t_data	data;

	if (error_check(&data, ac, av))
		return (data.error);
	if (init_data(&data, ac, av))
		return (data.error);
	if (start_dining(&data))
		return (data.error);
	return (0);
}