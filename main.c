/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:52:35 by hbray             #+#    #+#             */
/*   Updated: 2026/02/18 13:45:48 by hbray            ###   ########.fr       */
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
	t_data	data;
	t_philo *philos;

	if (argc < 5 || argc > 6)
		exit_error("Error: Invalid number of arguments\n");
	valid_nbr(argc, argv);
	if (init_data(&data,argc, argv) != 0)
		return (1);
	if (init_philo(&philos, &data) != 0)
		return (1);
	create_threads(philos, &data);
	join_pthread(&data, philos);
	return (0);
}
