/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:24:57 by jerrok            #+#    #+#             */
/*   Updated: 2022/04/14 14:25:57 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(pthread_t *threads, t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num)
	{
		if (pthread_create(&threads[i], 0, philo_routine, &philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&threads[i], 0, monitoring, philos))
		return (0);
	i = 0;
	while (i <= args->num)
	{
		pthread_join(threads[i], 0);
		i++;
	}
	return (1);
}

void	cleaner(t_philo *philos, t_args *args, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < args->num)
	{
		pthread_mutex_destroy(&philos[0].forks[i]);
		pthread_mutex_destroy(&philos[i].eating);
		i++;
	}
	pthread_mutex_destroy(&args->must_die);
	pthread_mutex_destroy(&args->check_time);
	pthread_mutex_destroy(&args->check_ate);
	free(args->eating);
	free(philos->forks);
	free(philos);
	free(threads);
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_philo		*philos;
	pthread_t	*threads;

	if (!check_and_parse(argc, argv, &args))
		printf("Error: argument\n");
	else
	{
		threads = malloc(sizeof(t_philo) * args.num + 1);
		if (!threads)
			return (1);
		philos = init_philos(&args);
		if (!philos)
		{
			free(threads);
			return (1);
		}
		if (!create_threads(threads, philos, &args))
		{
			free(threads);
			return (1);
		}
		cleaner(philos, &args, threads);
	}
	return (0);
}
