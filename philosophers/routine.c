/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:08:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/28 18:12:38 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_data *data, int index)
{
	pthread_mutex_lock(&data->forks[index]);
	if (print_action(data, index, "has taken a fork") == 1)
		return (1);
	pthread_mutex_lock(&data->forks[(index + 1)]);
	if (print_action(data, index, "has taken a fork") == 1)
		return (1);
	if (print_action(data, index, "is eating") == 1)
		return (1);
	data->philo[index].meals++;
	data->philo[index].last_eat = get_time();
	data->total_num_must_eat++;
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % data->num_philo]);
	return (0);
}

int	print_action(t_data *data, int index, char *str)
{
	int	time;

	time = get_time() - data->start_time;
	pthread_mutex_lock(&data->write_mutex);
	if (data->philo_dead == 1 || data->num_must_eat == data->philo[index].meals)
	{
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	printf("%-10d   %d %s\n", time, data->philo[index].philo_id, str);
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}

int	thinking(t_data *data, int index)
{
	if (print_action(data, index, "is thinking") == 1)
		return (1);
	return (0);
}

int	sleeping(t_data *data, int index)
{
	if (print_action(data, index, "is sleeping") == 1)
		return (1);
	usleep(data->time_to_sleep * 1000);
	return (0);
}


void	dest_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->think_mutex);
	pthread_mutex_destroy(&data->mutex);
}

int	philo_death(t_data *data, int index)
{
	int time;

	time = get_time() - data->philo[index].last_eat;
	if (time > data->time_to_die)
	{
		print_action(data, index, "died");
		dest_mutex(data);
		data->philo_dead = 1;
		return (1);
	}
	return (0);
}

void	*death(void *void_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)void_data;
	while (data->num_must_eat != -1 && (data->philo_dead == 0
			&& data->total_num_must_eat != data->num_must_eat))
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (data->philo[i].meals == data->num_must_eat)
				pthread_detach(data->philo[i].thread);
			if (philo_death(data, i) == 1)
				return NULL;
			i++;
		}
	}
	while (data->philo_dead == 0)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (philo_death(data, i) == 1)
				return NULL;
			i++;
		}
	}
	return (NULL);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
	// return time in milliseconds
}
