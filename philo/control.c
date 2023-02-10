/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:45:53 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/10 17:14:34 by yugurlu          ###   ########.fr       */
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
		system("leaks philo");
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
	pthread_mutex_destroy(&data->write_mutex);
}

int	all_philos_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->write_mutex);
		if (data->philo[i].meals != data->num_must_eat)
		{
			pthread_mutex_unlock(&data->write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->write_mutex);
		i++;
	}
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->write_mutex);
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->write_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->write_mutex);
	return (1);
}
