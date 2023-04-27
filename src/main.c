/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:45 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/27 14:12:51 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/*
FIX:
- sanitize errors with big amount of threads
- handle only 1 philosopher
	- only create 1 fork?
	- check if left and right are the same

Bottlenecks:
	- Philos should only check self alive
	- Philos have their own death_mutex
*/

void	message(t_philo *p, char *msg)
{
	pthread_mutex_lock(&(p->data->m_print));
	pthread_mutex_lock(&(p->data->m_main_lock));
	if (p->data->all_alive)
		printf("%-6llu %d %s\n", time_since(p->data->t_start), p->n + 1, msg);
	pthread_mutex_unlock(&(p->data->m_main_lock));
	pthread_mutex_unlock(&(p->data->m_print));
}

void	check_death(t_data *data)
{
	int	i;
	int	j;
	int	finished_philos;

	while (!(data->all_finished))
	{
		i = -1;
		while (++i < data->n_philo && data->all_alive)
		{
			pthread_mutex_lock(&(data->philo[i].m_last_eat));
			if (time_since(data->philo[i].t_last_eat) > data->t_die)
			{
				message(&(data->philo[i]), RED"died"WHITE);
				j = -1;
				while (++j < data->n_philo)
				{
					pthread_mutex_lock(&(data->philo[j].m_all_alive));
					data->philo[j].all_alive = 0;
					pthread_mutex_unlock(&(data->philo[j].m_all_alive));
				}
				pthread_mutex_lock(&(data->m_main_lock));
				pthread_mutex_lock(&(data->m_death));
				data->all_alive = 0;
				pthread_mutex_unlock(&(data->m_death));
				pthread_mutex_unlock(&(data->m_main_lock));
			}
			pthread_mutex_unlock(&(data->philo[i].m_last_eat));
			usleep(500);
		}
		if (!(data->all_alive))
			break ;
		i = -1;
		finished_philos = 0;
		while (++i < data->n_philo)
		{
			pthread_mutex_lock(&(data->philo[i].m_times_eaten));
			if (data->philo[i].times_eaten >= data->n_eat)
				finished_philos++;
			pthread_mutex_unlock(&(data->philo[i].m_times_eaten));
		}
		if (finished_philos == data->n_philo)
			data->all_finished = 1;
	}
}

// void	check_death(t_data *data)
// {
// 	int	i;

// 	while (!(data->all_finished))
// 	{
// 		i = -1;
// 		while (++i < data->n_philo && data->all_alive)
// 		{
// 			pthread_mutex_lock(&(data->m_death));
// 			if (time_since(data->philo[i].t_last_eat) > data->t_die)
// 			{
// 				message(&(data->philo[i]), RED"died"WHITE);
// 				pthread_mutex_lock(&(data->m_alive));
// 				data->all_alive = 0;
// 				pthread_mutex_unlock(&(data->m_alive));
// 			}
// 			pthread_mutex_unlock(&(data->m_death));
// 			usleep(500);
// 		}
// 		if (!(data->all_alive))
// 			break ;
// 		i = 0;
// 		pthread_mutex_lock(&(data->m_death));
// 		while (data->n_eat != -1 && i < data->n_philo && data->philo[i].times_eaten >= data->n_eat)
// 			i++;
// 		pthread_mutex_unlock(&(data->m_death));
// 		if (i == data->n_philo)
// 			data->all_finished = 1;
// 	}
// }

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