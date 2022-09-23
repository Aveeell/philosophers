/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:25:01 by jerrok            #+#    #+#             */
/*   Updated: 2022/04/14 13:11:06 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_args
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				dead;
	long long		start_time;
	pthread_mutex_t	must_die;
	pthread_mutex_t	check_time;
	pthread_mutex_t	check_ate;
	pthread_mutex_t	*eating;
}				t_args;

typedef struct s_philo
{
	int				id;
	int				ate;
	int				is_eating;
	long long		last_time_eat;
	t_args			*args;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating;
}				t_philo;

int			ft_atoi(const char *str);
int			check_and_parse(int argc, char **argv, t_args *args);
void		create_philo(pthread_mutex_t *forks, pthread_mutex_t *print,
				t_philo *philos, t_args *args);
t_philo		*init_philos(t_args *args);
long long	ft_time(void);
long long	ft_get_time(long long last);
void		ft_usleep(long long before, long long time);
void		*monitoring(void *arg);
void		*philo_routine(void *arg);
void		ft_print(int type, t_philo *philo);

#endif