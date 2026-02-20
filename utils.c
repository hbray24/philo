/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:02:37 by hbray             #+#    #+#             */
/*   Updated: 2026/02/20 11:20:47 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > 2147483647)
			break ;
		i++;
	}
	return (res);
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d %s\n", get_time_in_ms() - philo->data->start_time, philo->id,
		str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	monitor(t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philos->data->nb_philo)
		{
			if (get_time_in_ms()
				- philos[i].last_meal_time >= philos->data->time_to_die)
			{
				pthread_mutex_lock(&philos->data->dead_lock);
				philos->data->is_dead = 1;
				pthread_mutex_unlock(&philos->data->dead_lock);
				print_action(&philos[i], "is died");
				return ;
			}
			i++;
		}
	}
}
