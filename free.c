/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:38:52 by mimoreir          #+#    #+#             */
/*   Updated: 2023/08/29 10:38:53 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_philo *table)
{
	int		i;
	int		n;
	t_philo	*it;

	i = 0;
	n = table->inf->n_philos;
	it = table->next;
	pthread_mutex_destroy(&table->inf->write);
	pthread_mutex_destroy(&table->inf->read);
	pthread_mutex_destroy(&table->inf->eat_counter);
	free(table->inf);
	while (i < n)
	{
		pthread_mutex_destroy(&table->fork);
		free(table);
		table = it;
		i++;
		if (i == n)
			break ;
		it = it->next;
	}
}

void	ft_exit(t_philo *table)
{
	free_table(table);
	exit(EXIT_SUCCESS);
}
