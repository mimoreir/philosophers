/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:18:21 by mimoreir          #+#    #+#             */
/*   Updated: 2023/08/29 11:19:01 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*meals(void *data)
{
	t_philo		*table;
	int			i;

	i = 0;
	table = (t_philo *)data;
	while (i < table->inf->n_philos)
	{
		pthread_mutex_lock(&table->inf->eat_counter);
		if (table->meal_count == table->inf->times_must_eat)
		{
			table = table->next;
			i++;
		}
		pthread_mutex_unlock(&table->inf->eat_counter);
		if (verify_stop(table) == 1)
			break ;
	}
	pthread_mutex_lock(&table->inf->write);
	table->inf->stop = 1;
	pthread_mutex_unlock(&table->inf->write);
	return (NULL);
}

void	*death(void *data)
{
	t_philo		*table;
	long int	last;

	table = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&table->inf->read);
		last = table->last_meal;
		pthread_mutex_unlock(&table->inf->read);
		if (verify_last_meal((get_time() - table->inf->start_time), \
			last, table->inf->time_to_die))
		{
			pthread_mutex_lock(&table->inf->write);
			table->inf->stop = 1;
			pthread_mutex_unlock(&table->inf->write);
			writing(table, DIED);
			break ;
		}
		if (verify_stop(table) == 1)
			break ;
		table = table->next;
	}
	return (NULL);
}

void	start_simulation(t_philo *table)
{
	t_philo	*it;
	int		i;

	i = 0;
	it = table;
	table->inf->start_time = get_time();
	pthread_create(&it->inf->reaper, NULL, &death, (void *)table);
	if (table->inf->times_must_eat > 0)
		pthread_create(&it->inf->counter, NULL, &meals, (void *)table);
	while (i < table->inf->n_philos)
	{
		pthread_create(&it->th, NULL, &routine, (void *)it);
		it = it->next;
		i++;
	}
}

void	wait_threads(t_philo *table)
{
	t_philo	*it;
	int		i;

	i = 0;
	it = table;
	while (i < table->inf->n_philos)
	{
		pthread_join(it->th, NULL);
		it = it->next;
		i++;
	}
	pthread_join(it->inf->reaper, NULL);
	if (table->inf->times_must_eat > 0)
		pthread_join(it->inf->counter, NULL);
}

void	philosophers(t_philo *table)
{
	if (table->inf->n_philos == 1)
	{
		table->inf->start_time = get_time();
		writing(table, FORK);
		ft_usleep(table->inf->time_to_die + 1);
		writing(table, DIED);
	}
	else
	{
		start_simulation(table);
		wait_threads(table);
	}
	ft_exit(table);
}
