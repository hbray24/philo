/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:02:37 by hbray             #+#    #+#             */
/*   Updated: 2026/02/20 15:24:56 by hbray            ###   ########.fr       */
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
	if (check_death(philo->data) == 0)
		printf("%ld %d %s\n", get_time_in_ms() - philo->data->start_time,
			philo->id, str);
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
				pthread_mutex_lock(&philos->data->write_lock);
				printf("%ld %d died\n", get_time_in_ms()
					- philos->data->start_time, philos[i].id);
				pthread_mutex_lock(&philos->data->dead_lock);
				philos->data->is_dead = 1;
				pthread_mutex_unlock(&philos->data->dead_lock);
				pthread_mutex_unlock(&philos->data->write_lock);
				return ;
			}
			i++;
		}
	}
}

int	check_death(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_lock);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead);
}
