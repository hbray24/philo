/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:43:07 by hbray             #+#    #+#             */
/*   Updated: 2026/03/11 15:48:52 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			res;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void	ft_usleep(long time_ms, t_philo *philos)
{
	long	star_time;

	star_time = get_time_in_ms();
	while ((get_time_in_ms() - star_time) < time_ms
		&& check_finish(philos->data) == 0)
	{
		usleep(100);
	}
}
