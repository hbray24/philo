/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:02:37 by hbray             #+#    #+#             */
/*   Updated: 2026/02/23 13:03:02 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > 2147483647)
			break ;
		i++;
	}
	return (res);
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (check_finish(philo->data) == 0)
		printf("%ld %d %s\n", get_time_in_ms() - philo->data->start_time,
			philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}
