/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:37 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/08 16:20:06 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	error(char *str, t_data *data, int error_code)
{
	write(1, RED, 5);
	write(1, str, ft_strlen(str));
	write(1, WHITE, 4);
	data->error = error_code;
}

int	invalid_philo_input(t_data *data, char *input, int i)
{
	int	n;

	n = ft_atoi(input);
	if (n < 0 || (n == 0 && ft_strncmp(input, "0", 1) != 0))
		error("Only positive numbers allowed\n", data, 2 + i);
	else if (n > 200)
		error("Too many philosophers. (Max. 200)\n", data, 2 + i);
	return (data->error);
}

int	invalid_time_input(t_data *data, char *input, int i)
{
	int	n;

	n = ft_atoi(input);
	if (n < 0 || (n == 0 && ft_strncmp(input, "0", 1) != 0))
	{
		error("Only positive numbers allowed\n", data, 2 + i);
		return (data->error);
	}
	else if (n < 60)
	{
		error("Minimum 60ms required\n", data, 2 + i);
		return (data->error);
	}
	return (data->error);
}

int	invalid_eat_input(t_data *data, char *input, int i)
{
	int	n;

	n = ft_atoi(input);
	if (n <= 0)
		error("Only positive numbers allowed\n", data, 2 + i);
	return (data->error);
}

int	error_check(t_data *data, int ac, char *av[])
{
	int	i;

	data->error = 0;
	if (ac < 5)
		error("Not enough arguments.\n", data, 1);
	else if (ac > 6)
		error("Too many arguments.\n", data, 2);
	else
	{
		if (invalid_philo_input(data, av[1], 1))
			return (data->error);
		i = 1;
		while (++i < 5)
			if (invalid_time_input(data, av[i], i))
				return (data->error);
		if (ac == 6)
		{
			if (invalid_eat_input(data, av[i], i))
				return (data->error);
		}
		else
			data->n_eat = 2147483647;
	}
	return (data->error);
}
