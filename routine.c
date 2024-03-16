/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:19:13 by mimoreir          #+#    #+#             */
/*   Updated: 2023/08/29 11:56:03 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_to_sleep(t_philo *philo)
{
	writing(philo, SLEEPING);
	ft_usleep(philo->inf->time_to_sleep);
}

void	think(t_philo *philo)
{
	writing(philo, THINK);
	if (philo->inf->n_philos % 2 != 0)
		ft_usleep(20);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		writing(philo, FORK);
		pthread_mutex_lock(&philo->next->fork);
		writing(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		writing(philo, FORK);
		pthread_mutex_lock(&philo->fork);
		writing(philo, FORK);
	}
}

void	eat(t_philo *philo)
{
	writing(philo, EATING);
	pthread_mutex_lock(&philo->inf->read);
	philo->last_meal = get_time() - philo->inf->start_time;
	pthread_mutex_unlock(&philo->inf->read);
	pthread_mutex_lock(&philo->inf->eat_counter);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->inf->eat_counter);
	ft_usleep(philo->inf->time_to_eat);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->inf->read);
	philo->last_meal = get_time() - philo->inf->start_time;
	pthread_mutex_unlock(&philo->inf->read);
	if (philo->inf->n_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(10);
	}
	while (1)
	{
		if (verify_stop(philo) == 1)
			break ;
		take_forks(philo);
		eat(philo);
		go_to_sleep(philo);
		think(philo);
	}
	return (NULL);
}
