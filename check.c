/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:02:26 by hbray             #+#    #+#             */
/*   Updated: 2026/02/24 15:07:26 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philos)
{
	long	last_meal;

	pthread_mutex_lock(&philos->meal_lock);
	last_meal = philos->last_meal_time;
	pthread_mutex_unlock(&philos->meal_lock);
	if (get_time_in_ms() - last_meal >= philos->data->time_to_die)
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

	while (1)
	{
		i = -1;
		philos->data->finish_eat = 0;
		while (++i < philos->data->nb_philo)
		{
			if (check_death(&philos[i]))
				return ;
			pthread_mutex_lock(&philos[i].meal_lock);
			if (philos->data->goal_eat != -1
				&& philos->data->goal_eat == philos[i].nb_eat)
				philos->data->finish_eat++;
			pthread_mutex_unlock(&philos[i].meal_lock);
		}
		if (philos->data->goal_eat != -1
			&& philos->data->nb_philo <= philos->data->finish_eat)
		{
			pthread_mutex_lock(&philos->data->finish_lock);
			philos->data->is_finish = 1;
			pthread_mutex_unlock(&philos->data->finish_lock);
			return ;
		}
		ft_usleep(1000);
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
