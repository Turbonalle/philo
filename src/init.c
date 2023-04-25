/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:57:19 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/25 16:48:55 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	init_data(t_data *data, int ac, char *av[])
{
	data->n_philo = atoi(av[1]);
	data->t_die = atoi(av[2]);
	data->t_eat = atoi(av[3]);
	data->t_sleep = atoi(av[4]);
	if (ac == 6)
		data->n_eat = atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!(data->philo))
		error("Malloc failed\n", data, 8);
	return (data->error);
}



pthread_mutex_t *init_mutex(t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

// void	init_mutex(t_data *data)
// {
// 	pthread_mutex_t forks[data->n_philo];
// 	int i;

// 	i = 0;
// 	data->forks = forks;
// 	while (i < data->n_philo)
// 	{
// 		pthread_mutex_init(&data->forks[i], NULL);
// 		i++;
// 	}
// }

void	choose_forks(t_philo *p)
{
	if (p->n % 2 == 0)
		p->fork1 = p->n % p->data->n_philo;
	else
		p->fork1 = p->n - 1;
	if (p->n % 2 == 0)
		p->fork2 = p->n - 1;
	else	
		p->fork2 = p->n % p->data->n_philo;
}



void	init_philo(t_data *data)
{
	int i;
	
	i = -1;
	data->all_alive = 1;
	start_time(data);
	while (++i < data->n_philo)
	{
		usleep(10);
		data->philo[i].data = data;
		data->philo[i].n = i + 1;
		data->philo[i].finished = 0;
		data->philo[i].times_eaten = 0;
		choose_forks(&(data->philo[i]));
		data->philo[i].t_last_eat = data->t_start;
		if (pthread_create(&(data->philo[i].thread), NULL, &philosopher, &(data->philo[i])) != 0)
			error("Failed to create thread\n", data, 9);
	}
}