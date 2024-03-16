/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:48:39 by mimoreir          #+#    #+#             */
/*   Updated: 2023/08/29 11:00:10 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verify_last_meal(long int cur, long int last, int t_die)
{
	if (cur - last >= t_die)
		return (1);
	return (0);
}

void	stop_sim(t_philo *table)
{
	pthread_mutex_lock(&table->inf->write);
	table->inf->stop = 1;
	pthread_mutex_unlock(&table->inf->write);
	writing(table, DIED);
}

int	verify_stop(t_philo *table)
{
	pthread_mutex_lock(&table->inf->write);
	if (table->inf->stop == 1)
	{
		pthread_mutex_unlock(&table->inf->write);
		return (1);
	}
	pthread_mutex_unlock(&table->inf->write);
	return (0);
}
