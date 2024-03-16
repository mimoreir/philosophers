/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:40:28 by mimoreir          #+#    #+#             */
/*   Updated: 2023/08/29 10:40:30 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (*str == '-')
		return (0);
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	verify_args(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	num = 0;
	while (i < argc)
	{
		if (is_valid_number(argv[i]))
		{
			num = ft_atoi(argv[i]);
			if (num < 1)
			{
				printf("Something wrong on arguments\n");
				return (0);
			}
		}
		else
		{
			printf("Something wrong on arguments\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info	*info;
	t_philo	*table;

	table = NULL;
	info = NULL;
	if (argc == 5 || argc == 6)
	{
		if (!verify_args(argc, argv))
			return (0);
		info = load_info(argc, argv);
		table = create_table(info);
		philosophers(table);
	}
	else
		printf("Number of arguments invalid\n");
	if (table)
		free_table(table);
	return (0);
}
