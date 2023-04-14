/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:57:37 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/14 16:03:36 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	error(char *str, t_data *data, int error_code)
{
	write(1, RED, 5);
	write(1, str, strlen(str));
	write(1, WHITE, 4);
	data->error = error_code;
}

int	error_check(t_data *data, int ac, char *av[])
{
	data->error = 0;
	if (ac < 5)
		error("Not enough arguments.\n", data, 1);
	else if (ac > 6)
		error("Too many arguments.\n", data, 2);
	else
	{
		if (atoi(av[1]) == 0 && strncmp(av[1], "0", 1) != 0)
			error("Wrong input [1]\n", data, 3);
		if (atoi(av[2]) == 0 && strncmp(av[2], "0", 1) != 0)
			error("Wrong input [2]\n", data, 4);
		if (atoi(av[3]) == 0 && strncmp(av[3], "0", 1) != 0)
			error("Wrong input [3]\n", data, 5);
		if (atoi(av[4]) == 0 && strncmp(av[4], "0", 1) != 0)
			error("Wrong input [4]\n", data, 6);
		if (ac == 6 && atoi(av[5]) == 0 && strncmp(av[4], "0", 1) != 0)
			error("Wrong input [5]\n", data, 7);
	}
	return (data->error);
}