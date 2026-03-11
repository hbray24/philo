/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 08:56:06 by hbray             #+#    #+#             */
/*   Updated: 2026/03/11 10:23:31 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	verif_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	if (!('0' <= str[i] && str[i] <= '9'))
		return (0);
	while ('0' <= str[i] && str[i] <= '9')
		i++;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	valid_nbr(int argc, char **argv)
{
	long	nb;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			return (1);
		if (!verif_nbr(argv[i]))
			return (1);
		nb = ft_atol(argv[i]);
		if (i == 1)
		{
			if (nb > INT_MAX || nb <= 0)
				return (1);
		}
		else
		{
			if (nb > INT_MAX || nb < 0)
				return (1);
		}
		i++;
	}
	return (0);
}
