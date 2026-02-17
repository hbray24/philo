/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:23:06 by hbray             #+#    #+#             */
/*   Updated: 2026/02/17 13:36:13 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
}					t_philo;

long				get_time_in_ms(void);
long				ft_atol(const char *str);
void				valid_nbr(int argc, char **argv);
void				exit_error(char *str);
#endif