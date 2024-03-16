/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:39:24 by mimoreir          #+#    #+#             */
/*   Updated: 2023/08/29 10:56:54 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <malloc.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdarg.h>
# include <pthread.h>
# include <sys/time.h>

enum
{
	DIED,
	FORK,
	EATING,
	SLEEPING,
	THINK
};

typedef struct s_info
{
	pthread_t		reaper;
	pthread_t		counter;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long int		start_time;
	int				stop;
	pthread_mutex_t	write;
	pthread_mutex_t	read;
	pthread_mutex_t	eat_counter;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		th;
	long int		last_meal;
	int				n_forks;
	int				meal_count;
	int				status;
	pthread_mutex_t	fork;
	t_info			*inf;
	struct s_philo	*next;
}	t_philo;

int			ft_isdigit(int c);
int			ft_atoi(const char *ptr);
long int	get_time(void);
void		ft_usleep(long int time);
t_info		*load_info(int argc, char *argv[]);
t_philo		*create_table(t_info *info);
void		free_table(t_philo *table);
void		philosophers(t_philo *table);
void		*routine(void *data);
void		writing(t_philo *philo, int action);
void		wait_threads(t_philo *table);
void		ft_exit(t_philo *table);
int			verify_last_meal(long int cur, long int last, int t_die);
void		stop_sim(t_philo *table);
int			verify_stop(t_philo *table);

#endif
