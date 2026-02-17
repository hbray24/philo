/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:52:35 by hbray             #+#    #+#             */
/*   Updated: 2026/02/17 10:52:27 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*mon_philo;

	mon_philo = (t_philo *)arg;
	printf("je suis le thread%d\n", mon_philo->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
		long start_time;
		int i;
		int nb_of_philo;
		pthread_t *threads;
		t_philo *philos;
		pthread_mutex_t *forks;

	if (argc == 5 || argc == 6)
	{
		valid_nbr(argc, argv);
		i = 0;
		nb_of_philo = (int)ft_atol(argv[1]);
		start_time = get_time_in_ms();
		threads = malloc(sizeof(pthread_t) * nb_of_philo);
		philos = malloc(sizeof(t_philo) * nb_of_philo);
		forks = malloc(sizeof(pthread_mutex_t) * nb_of_philo);
		while (i < nb_of_philo)
		{
			pthread_mutex_init(&forks[i], NULL);
			i++;
		}
		i = 0;
		while (i < nb_of_philo)
		{
			philos[i].id = i + 1;
			philos[i].left_fork = &forks[i];
			philos[i].time_to_die = (int)ft_atol(argv[2]);
			philos[i].time_to_eat = (int)ft_atol(argv[3]);
			philos[i].time_to_sleep = (int)ft_atol(argv[4]);
			if (argc == 6)
				philos[i].number_eat = ft_atol(argv[5]);
			else 
				philos[i].number_eat = -1;
			if (i == nb_of_philo - 1)
				philos[i].right_fork = &forks[0];
			else
				philos[i].right_fork = &forks[i + 1];
			if(pthread_create(&threads[i], NULL, routine, &philos[i]) != 0)
				printf("Error thread\n");
			i++;
		}
		i = 0;
		while (i < nb_of_philo)
		{
			pthread_join(threads[i], NULL);
			i++;
		}
		i = 0;
		while (i < nb_of_philo)
		{
			pthread_mutex_destroy(forks);
			i++;
		}
		free(threads);
		free(philos);
		free(forks);
		return (0);
	}
	else
	{
		printf("Error\n");
		return (0);
	}
}
