/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:52:35 by hbray             #+#    #+#             */
/*   Updated: 2026/03/12 11:08:11 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		if (philo->data->nb_philo == 1)
		{
			ft_usleep(philo->data->time_to_die, philo);
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	return (0);
}

static int	philo_cycle(t_philo *philo)
{
	long	time_to_think;

	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->nb_eat += 1;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->nb_eat == philo->data->goal_eat)
		return (1);
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
	print_action(philo, "is thinking");
	if (philo->data->nb_philo % 2 != 0)
	{
		time_to_think = 2 * philo->data->time_to_eat
			- philo->data->time_to_sleep;
	}
	else
		time_to_think = philo->data->time_to_eat - philo->data->time_to_sleep;
	if (time_to_think > 0)
		ft_usleep(time_to_think, philo);
	return (0);
}

static void	wait_for_ready(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->finish_lock);
		if (philo->data->ready == 1)
		{
			pthread_mutex_unlock(&philo->data->finish_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->finish_lock);
		usleep(100);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_ready(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->data->goal_eat == 0)
		return (NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	while (check_finish(philo->data) == 0)
	{
		if (take_forks(philo))
			break ;
		if (philo_cycle(philo))
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (ft_parsing(argc, argv) != 0)
		return (1);
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philo(&philos, &data) != 0)
		return (1);
	if (create_threads(philos) != 0)
		return (1);
	pthread_mutex_lock(&data.finish_lock);
	data.start_time = get_time_in_ms();
	data.ready = 1;
	pthread_mutex_unlock(&data.finish_lock);
	monitor(philos);
	join_pthread(&data, philos);
	destroy_mutex(&data, philos);
	all_free(philos, &data);
	return (0);
}
