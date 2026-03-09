/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:02:26 by hbray             #+#    #+#             */
/*   Updated: 2026/03/09 14:38:54 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d died\n", get_time_in_ms() - philo->data->start_time,
		philo->id);
	pthread_mutex_lock(&philo->data->finish_lock);
	philo->data->is_finish = 1;
	pthread_mutex_unlock(&philo->data->finish_lock);
	pthread_mutex_unlock(&philo->data->write_lock);
	return (1);
}

static int	check_finish_eat(t_philo *philo, int finish_eat)
{
	if (philo->data->goal_eat != -1 && philo->data->nb_philo <= finish_eat)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		pthread_mutex_lock(&philo->data->finish_lock);
		philo->data->is_finish = 1;
		pthread_mutex_unlock(&philo->data->finish_lock);
		pthread_mutex_unlock(&philo->data->write_lock);
		return (1);
	}
	return (0);
}

static int	check_philo(t_philo *philo, int *finish_eat)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time_in_ms() - philo->last_meal_time >= philo->data->time_to_die)
		dead = 1;
	else if (philo->data->goal_eat != -1
		&& philo->nb_eat >= philo->data->goal_eat)
		(*finish_eat)++;
	pthread_mutex_unlock(&philo->meal_lock);
	if (dead)
		return (philo_dead(philo));
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
			if (check_philo(&philos[i], &finish_eat))
				return ;
		}
		if (check_finish_eat(philos, finish_eat))
			return ;
		ft_usleep(2);
	}
}

int	check_finish(t_data *data)
{
	int	finish;

	pthread_mutex_lock(&data->finish_lock);
	finish = data->is_finish;
	pthread_mutex_unlock(&data->finish_lock);
	return (finish);
}
