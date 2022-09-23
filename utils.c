/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:32:55 by jerrok            #+#    #+#             */
/*   Updated: 2022/04/07 12:59:32 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(int type, t_philo *philo)
{
	long long	start_time;
	int			id;

	id = philo->id;
	start_time = philo->args->start_time;
	pthread_mutex_lock(&philo->args->must_die);
	if (philo->args->dead)
	{
		pthread_mutex_unlock(&philo->args->must_die);
		return ;
	}
	pthread_mutex_unlock(&philo->args->must_die);
	if (type == 1)
		printf("%lld %d has taken a fork\n", ft_get_time(start_time), id);
	if (type == 2)
		printf("%lld %d is eating\n", ft_get_time(start_time), id);
	if (type == 3)
		printf("%lld %d is sleeping\n", ft_get_time(start_time), id);
	if (type == 4)
		printf("%lld %d is thinking\n", ft_get_time(start_time), id);
}

long long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	ft_get_time(long long last)
{
	return (ft_time() - last);
}

void	ft_usleep(long long before, long long time)
{
	while (ft_time() < (before + time))
		usleep(500);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					neg;
	unsigned long long	res;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (neg == -1 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (res > 9223372036854775807ULL)
	{
		if (neg == 1)
			return (-1);
		return (0);
	}
	return ((int)res * neg);
}
