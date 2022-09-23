/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:08:50 by jerrok            #+#    #+#             */
/*   Updated: 2022/04/08 11:40:48 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_die(long long time_btw_eating, t_philo *philos, int i)
{
	if (time_btw_eating > philos[i].args->time_to_die && !philos[i].is_eating)
	{
		pthread_mutex_lock(&(philos[i].args->must_die));
		philos->args->dead = 1;
		pthread_mutex_unlock(&(philos[i].args->must_die));
		printf("%lld %d died\n", ft_get_time(philos[i].args->start_time),
			philos[i].id);
		return (0);
	}
	return (1);
}

static int	check_philo(t_philo *philos, int i, int *j)
{
	long long	time_btw_eating;

	pthread_mutex_lock(&philos->args->check_time);
	time_btw_eating = ft_time() - philos[i].last_time_eat;
	pthread_mutex_unlock(&philos->args->check_time);
	if (!check_die(time_btw_eating, philos, i))
		return (0);
	pthread_mutex_lock(&philos->args->check_ate);
	if (philos[i].ate == 1)
		(*j)++;
	pthread_mutex_unlock(&philos->args->check_ate);
	if (*j == philos[0].args->must_eat)
	{
		pthread_mutex_lock(&(philos[i].args->must_die));
		philos[i].args->dead = 1;
		pthread_mutex_unlock(&(philos[i].args->must_die));
		return (0);
	}
	return (1);
}

void	*monitoring(void *arg)
{
	t_philo	*philos;
	int		i;
	int		j;

	j = 0;
	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].args->num)
		{
			if (!check_philo(philos, i, &j))
				return (0);
			i++;
		}
	}
}
