/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:08:24 by mimoreir          #+#    #+#             */
/*   Updated: 2023/08/29 11:08:43 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *ptr)
{
	int		res;
	int		sign;
	char	*it;

	res = 0;
	sign = 1;
	it = (char *)ptr;
	while (*it == ' ' || (*it >= 9 && *it <= 13))
		it++;
	if (*it == '-' || *it == '+')
	{
		if (*it == '-')
			sign = -1;
		it++;
	}
	while (*it && *it >= '0' && *it <= '9')
	{
		res = res * 10 + (*it - '0');
		it++;
	}
	return (res * sign);
}

long int	get_time(void)
{
	long int		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time)
{
	long int	start;

	start = get_time();
	while (get_time() - start < time)
	{
		usleep(time / 10);
	}
}

void	writing(t_philo *philo, int action)
{
	long int	cur;

	pthread_mutex_lock(&philo->inf->write);
	cur = get_time() - philo->inf->start_time;
	philo->status = action;
	if (action == EATING && !philo->inf->stop)
		printf("%10ld %3d is eating\n", cur, philo->id);
	if (action == SLEEPING && !philo->inf->stop)
		printf("%10ld %3d is sleeping\n", cur, philo->id);
	if (action == THINK && !philo->inf->stop)
		printf("%10ld %3d is thinking\n", cur, philo->id);
	if (action == FORK && !philo->inf->stop)
		printf("%10ld %3d has taken a fork\n", cur, philo->id);
	if (action == DIED)
		printf("%10ld %3d died\n", cur, philo->id);
	pthread_mutex_unlock(&philo->inf->write);
}
