/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:51:43 by jbagger           #+#    #+#             */
/*   Updated: 2023/05/04 18:25:23 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	message(t_philo *p, char *msg)
{
	pthread_mutex_lock(&(p->data->m_all_alive));
	if (p->data->all_alive)
		printf("%-6ld %d %s\n", time_since(p->data->t_start), p->n + 1, msg);
	pthread_mutex_unlock(&(p->data->m_all_alive));
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*str >= 8 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
		str++;
	}
	return (result * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i + 1 < n)
	{
		if (!s1[i] && !s2[i])
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
