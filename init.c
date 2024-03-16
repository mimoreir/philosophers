/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:40:12 by mimoreir          #+#    #+#             */
/*   Updated: 2023/08/29 10:40:13 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*load_info(int argc, char *argv[])
{
	int		i;
	t_info	*info;

	info = malloc(sizeof(t_info));
	i = 1;
	info->n_philos = ft_atoi(argv[i++]);
	info->time_to_die = ft_atoi(argv[i++]);
	info->time_to_eat = ft_atoi(argv[i++]);
	info->time_to_sleep = ft_atoi(argv[i++]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[i++]);
	else
		info->times_must_eat = 0;
	info->stop = 0;
	pthread_mutex_init(&info->write, NULL);
	pthread_mutex_init(&info->read, NULL);
	pthread_mutex_init(&info->eat_counter, NULL);
	return (info);
}

t_philo	*new_philo(int id, t_info *info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->inf = info;
	new->meal_count = 0;
	new->status = 2;
	new->last_meal = 0;
	new->n_forks = 1;
	pthread_mutex_init(&new->fork, NULL);
	new->next = NULL;
	return (new);
}

void	add_last(t_philo *table, t_philo *new)
{
	t_philo	*it;

	it = table;
	while (it->next != NULL)
		it = it->next;
	it->next = new;
}

void	last_philo(t_philo *table)
{
	t_philo	*it;

	it = table;
	while (it->next != NULL)
		it = it->next;
	it->next = table;
}

t_philo	*create_table(t_info *info)
{
	t_philo	*table;
	t_philo	*new;
	int		i;

	i = 0;
	new = new_philo(i++ + 1, info);
	if (!new)
		return (NULL);
	table = new;
	while (i < info->n_philos)
	{
		new = new_philo(i + 1, info);
		add_last(table, new);
		i++;
	}
	last_philo(table);
	return (table);
}
