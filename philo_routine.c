/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:10:02 by jerrok            #+#    #+#             */
/*   Updated: 2022/07/12 17:28:41 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo, int first, int second)
{
	long long	time;

	pthread_mutex_lock(&philo->forks[first]);
	ft_print(1, philo);
	if (second == first)
	{
		usleep(philo->args->time_to_die * 1000);
		return ;
	}
	pthread_mutex_lock(&philo->forks[second]);
	ft_print(1, philo);
	pthread_mutex_lock(&philo->eating);
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->eating);
	ft_print(2, philo);
	pthread_mutex_lock(&philo->args->check_time);
	philo->last_time_eat = ft_time();
	time = philo->last_time_eat;
	pthread_mutex_unlock(&philo->args->check_time);
	ft_usleep(time, philo->args->time_to_eat);
	pthread_mutex_lock(&philo->eating);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->forks[second]);
	pthread_mutex_unlock(&philo->forks[first]);
}

static void	start_dinner(t_philo *philo, int first, int second)
{
	int			i;
	long long	time_after_eat;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->args->must_die);
		if (philo->args->dead)
		{
			pthread_mutex_unlock(&philo->args->must_die);
			return ;
		}
		pthread_mutex_unlock(&philo->args->must_die);
		eating(philo, first, second);
		pthread_mutex_lock(&philo->args->check_ate);
		if (i++ == philo->args->must_eat)
			philo->ate = 1;
		pthread_mutex_unlock(&philo->args->check_ate);
		ft_print(3, philo);
		pthread_mutex_lock(&philo->args->check_time);
		time_after_eat = philo->last_time_eat + philo->args->time_to_eat;
		pthread_mutex_unlock(&philo->args->check_time);
		ft_usleep(time_after_eat, philo->args->time_to_sleep);
		ft_print(4, philo);
	}
}

static void	choose_forks(int *first, int *second, t_philo *philo)
{
	if (philo->id == 1)
	{
		*first = philo->args->num - 1;
		*second = philo->id - 1;
	}
	else
	{
		*first = philo->id - 2;
		*second = philo->id - 1;
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		first;
	int		second;

	philo = (t_philo *)arg;
	choose_forks(&first, &second, philo);
	if (philo->id % 2 == 0)
		usleep(100);
	start_dinner(philo, first, second);
	return (0);
}
