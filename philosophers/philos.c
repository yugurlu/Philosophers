/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:41 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/30 16:00:01 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_data(t_data *data, char **av)
{
	data->num_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (data->num_philo < 1)
	{
		printf("Error: Wrong argument!\n");
		return (1);
	}
	if (av[5])
	{
		if (atoi(av[5]) < 1)
		{
			printf("Error: Wrong argument!\n");
			return (1);
		}
		data->num_must_eat = atoi(av[5]);
		data->total_num_must_eat = data->num_must_eat * data->num_philo;
	}
	else
		data->num_must_eat = -1;
	return (0);
}

void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].num_must_meals = data->num_must_eat;
		data->philo[i].meals = 0;
		data->philo[i].last_eat = get_time();
		i++;
	}
	data->philo_dead = 0;
	data->thread_number = 0;
}

void	*one_philo(void *void_data)
{
	t_data	*data;

	data = (t_data *)void_data;
	data->start_time = get_time();
	print_action(data, 0, "has taken a fork");
	smart_sleep(data->time_to_eat);
	print_action(data, 0, "died");
	destroy(data);
	return (NULL);
}

int	philo_death(t_data *data, int index)
{
	int	time;

	pthread_mutex_lock(&data->proc);
	time = get_passed_time(data->philo[index].last_eat);
	if (time > data->time_to_die)
	{
		pthread_mutex_unlock(&data->proc);
		print_action(data, index, "died");
		pthread_mutex_lock(&data->proc);
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->proc);
		return (1);
	}
	pthread_mutex_unlock(&data->proc);
	return (0);
}

void	*death(void *void_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)void_data;
	while (data->philo_dead == 0)
	{
		i = 0;
		pthread_mutex_lock(&data->proc);
		if (data->total_num_must_eat == data->num_must_eat)
		{
			pthread_mutex_unlock(&data->proc);
			break ;
		}
		pthread_mutex_unlock(&data->proc);
		while (i < data->num_philo)
		{
			if (philo_death(data, i) == 1)
				break ;
			i++;
		}
	}
	return (NULL);
}
