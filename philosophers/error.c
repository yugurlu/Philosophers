/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:41 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/28 12:46:31 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	control(int ac, char **arg)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments!\n");
		return (1);
	}
	while (arg[j])
	{
		while (arg[j][i])
		{
			if (arg[j][i] < '0' || arg[j][i] > '9')
			{
				printf("Error: Wrong argument!\n");
				return (1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

int	get_data(t_data *data, char **av)
{
	data->num_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (data->num_philo < 1)
	{
		printf("Error: Wrong argument!\n");
		//free
		return (1);
	}
	if (av[5])
	{
		if (atoi(av[5]) < 1)
		{
			printf("Error: Wrong argument!\n");
			//free
			return (1);
		}
		data->num_must_eat = atoi(av[5]);
		data->total_num_must_eat = data->num_must_eat * data->num_philo;
	}
	else
		data->num_must_eat = -1;
	return (0);
}
