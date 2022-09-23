/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:24:20 by jerrok            #+#    #+#             */
/*   Updated: 2022/04/14 13:35:03 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(pthread_mutex_t *forks, pthread_mutex_t *eating,
					t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	pthread_mutex_init(&args->check_time, 0);
	pthread_mutex_init(&args->check_ate, 0);
	while (i < args->num)
	{
		pthread_mutex_init(&eating[i], 0);
		pthread_mutex_init(&forks[i], 0);
		i++;
	}
	args->eating = eating;
	i = 0;
	while (i < args->num)
	{
		philos[i].id = i + 1;
		philos[i].ate = 0;
		philos[i].last_time_eat = args->start_time;
		philos[i].args = args;
		philos[i].forks = forks;
		philos[i].is_eating = 0;
		philos[i].eating = eating[i];
		i++;
	}
}

t_philo	*init_philos(t_args *args)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eating;

	philos = malloc(sizeof(t_philo) * args->num);
	if (!philos)
		return (NULL);
	forks = malloc(sizeof(pthread_mutex_t) * args->num);
	if (!forks)
	{	
		free(philos);
		return (NULL);
	}
	eating = malloc(sizeof(pthread_mutex_t) * args->num);
	if (!eating)
	{
		free(forks);
		free(philos);
		return (NULL);
	}
	create_philo(forks, eating, philos, args);
	return (philos);
}

int	check_and_parse(int argc, char **argv, t_args *args)
{
	if (argc == 5 || argc == 6)
	{
		args->num = ft_atoi(argv[1]);
		args->time_to_die = ft_atoi(argv[2]);
		args->time_to_eat = ft_atoi(argv[3]);
		args->time_to_sleep = ft_atoi(argv[4]);
		args->dead = 0;
		args->must_eat = -1;
		args->start_time = ft_time();
		pthread_mutex_init(&(args->must_die), NULL);
		if (argc == 6)
			args->must_eat = ft_atoi(argv[5]);
		if (args->num <= 0 || args->time_to_die <= 0 || args->time_to_eat <= 0
			|| args->time_to_sleep <= 0 || (argc == 6 && args->must_eat <= 0))
			return (0);
		return (1);
	}
	return (0);
}
