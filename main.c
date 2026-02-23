/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:52:35 by hbray             #+#    #+#             */
/*   Updated: 2026/02/23 09:48:21 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (check_death(philo->data) == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		if (philo->data->nb_philo == 1)
		{
			ft_usleep(philo->data->time_to_die);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		philo->last_meal_time = get_time_in_ms();
		philo->nb_eat += 1;
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		exit_error("Error: Invalid number of arguments\n");
	valid_nbr(argc, argv);
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philo(&philos, &data) != 0)
		return (1);
	if (create_threads(philos) != 0)
		return (1);
	monitor(philos);
	join_pthread(&data, philos);
	all_free(philos, &data);
	return (0);
}
