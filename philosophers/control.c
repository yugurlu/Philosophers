/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:45:53 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/31 17:40:54 by yugurlu          ###   ########.fr       */
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
		printf("%sError: Wrong number of arguments!\n", "\e[31m");
		return (1);
	}
	while (arg[j])
	{
		while (arg[j][i])
		{
			if (arg[j][i] < '0' || arg[j][i] > '9')
			{
				printf("%sError: Wrong argument!\n", "\e[31m");
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
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->num_philo < 1)
	{
		printf("%sError: Wrong argument!\n", "\e[31m");
		return (1);
	}
	if (av[5])
	{
		if (ft_atoi(av[5]) < 1)
		{
			printf("%sError: Wrong argument!\n", "\e[31m");
			return (1);
		}
		data->num_must_eat = ft_atoi(av[5]);
		data->total_num_must_eat = data->num_must_eat * data->num_philo;
	}
	else
		data->num_must_eat = -1;
	return (0);
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	i = 0;
	while (i < data->num_philo)
		pthread_detach(data->philo[i++].thread);
	pthread_mutex_destroy(&data->proc);
	pthread_mutex_destroy(&data->write_mutex);
}
