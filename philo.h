/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:23:06 by hbray             #+#    #+#             */
/*   Updated: 2026/02/18 13:41:41 by hbray            ###   ########.fr       */
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

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
}					t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
}					t_philo;

void				*routine(void *arg);
long				get_time_in_ms(void);
long				ft_atol(const char *str);
void				valid_nbr(int argc, char **argv);
void				exit_error(char *str);
void				all_free(pthread_t *threads, t_philo *philos,
						pthread_mutex_t *forks);
int					init_data(t_data *data, int argc, char **argv);
int					init_philo(t_philo **philos, t_data *data);
int					create_threads(t_philo *philos, t_data *data);
int					join_pthread(t_data *data, t_philo *philos);
int					destroy_mutex(t_data *data);

#endif