/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:45 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/09 13:56:33 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	main(int ac, char *av[])
{
	t_data	data;

	data.color = ON;
	if (error_check(&data, ac, av))
		return (data.error);
	if (init_data(&data, ac, av))
		return (data.error);
	if (init_mutex(&data))
		return (data.error);
	if (init_philo(&data))
		return (data.error);
	check_death(&data);
	join_threads(&data, data.n_philo);
	destroy_forks(&data, data.n_philo);
	return (0);
}
