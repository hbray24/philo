/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:04:27 by hbray             #+#    #+#             */
/*   Updated: 2026/02/23 13:57:24 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->goal_eat = ft_atol(argv[5]);
	else
		data->goal_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->is_finish = 0;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->finish_lock, NULL);
	data->start_time = get_time_in_ms();
	return (0);
}

int	init_philo(t_philo **philos, t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philos)
		return (1);
	philo_tmp = *philos;
	while (i < data->nb_philo)
	{
		philo_tmp[i].id = i + 1;
		philo_tmp[i].data = data;
		philo_tmp[i].left_fork = &data->forks[i];
		philo_tmp[i].last_meal_time = data->start_time;
		if (i == data->nb_philo - 1)
			philo_tmp[i].right_fork = &data->forks[0];
		else
			philo_tmp[i].right_fork = &data->forks[i + 1];
		if (data->goal_eat != -1)
			philo_tmp[i].nb_eat = 0;
		else
			philo_tmp[i].nb_eat = -1;
		i++;
	}
	return (0);
}

int	create_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
