/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:52:35 by hbray             #+#    #+#             */
/*   Updated: 2026/03/11 14:35:30 by hbray            ###   ########.fr       */
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
	long	thinking_time;

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
		thinking_time = (philo->data->time_to_die - philo->data->time_to_eat
				- philo->data->time_to_sleep) / 2;
		if (thinking_time > 0)
			ft_usleep(thinking_time, philo);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->data->goal_eat == 0)
		return (NULL);
	if (philo->id % 2 == 0)
		ft_usleep(10, philo);
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

	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Invalid number of arguments\n", 36);
		return (1);
	}
	if (valid_nbr(argc, argv))
	{
		write(2, "Error: Invalid arguments\n", 26);
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philo(&philos, &data) != 0)
		return (1);
	if (create_threads(philos) != 0)
		return (1);
	monitor(philos);
	join_pthread(&data, philos);
	destroy_mutex(&data, philos);
	all_free(philos, &data);
	return (0);
}
