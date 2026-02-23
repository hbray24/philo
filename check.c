/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:02:26 by hbray             #+#    #+#             */
/*   Updated: 2026/02/23 14:46:05 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philos)
{
	if (get_time_in_ms() - philos->last_meal_time >= philos->data->time_to_die)
	{
		pthread_mutex_lock(&philos->data->write_lock);
		printf("%ld %d died\n", get_time_in_ms() - philos->data->start_time,
			philos->id);
		pthread_mutex_lock(&philos->data->finish_lock);
		philos->data->is_finish = 1;
		pthread_mutex_unlock(&philos->data->finish_lock);
		pthread_mutex_unlock(&philos->data->write_lock);
		return (1);
	}
	return (0);
}

void	monitor(t_philo *philos)
{
	int	i;
	int	finish_eat;

	while (1)
	{
		i = -1;
		finish_eat = 0;
		while (++i < philos->data->nb_philo)
		{
			if (check_death(&philos[i]))
				return ;
			if (philos->data->goal_eat == philos[i].nb_eat)
				finish_eat++;
		}
		if (philos->data->goal_eat == finish_eat)
		{
			pthread_mutex_lock(&philos->data->finish_lock);
			philos->data->is_finish = 1;
			pthread_mutex_unlock(&philos->data->finish_lock);
			return ;
		}
	}
}

int	check_finish(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->finish_lock);
	dead = data->is_finish;
	pthread_mutex_unlock(&data->finish_lock);
	return (dead);
}
