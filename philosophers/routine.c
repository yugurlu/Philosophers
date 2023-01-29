/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:08:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/29 19:42:00 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *void_data)
{
	int		index;
	t_data	*data;

	data = (t_data *)void_data;
	pthread_mutex_lock(&data->proc);
	index = data->thread_number;
	pthread_mutex_unlock(&data->proc);
	while (data->philo_dead != 1)
	{
		if (eating(data, index) == 1)
			break ;
		if (data->num_must_eat != data->philo[index].meals)
		{
			if (sleeping(data, index) == 1)
				break ;
			if (thinking(data, index) == 1)
				break ;
		}
		else
			break ;
	}

	return (NULL);
}

int	eating(t_data *data, int index)
{
	pthread_mutex_lock(&data->forks[index]);
	if (print_action(data, index, "has taken a fork") == 1)
		return (1);
	pthread_mutex_lock(&data->forks[(index + 1) % data->num_philo]);
	if (print_action(data, index, "has taken a fork") == 1)
		return (1);
	if (print_action(data, index, "is eating") == 1)
		return (1);
	pthread_mutex_lock(&data->proc);
	data->philo[index].meals++;
	data->total_num_must_eat++;
	data->philo[index].last_eat = get_time();
	pthread_mutex_unlock(&data->proc);
	smart_sleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % data->num_philo]);
	return (0);
}

int	print_action(t_data *data, int index, char *str)
{
	int	time;

	pthread_mutex_lock(&data->write_mutex);
	time = get_passed_time(data->start_time);
	if (data->num_must_eat == data->philo[index].meals)
	{
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	//pthread_mutex_lock(&data->proc);
	pthread_mutex_lock(&data->maymunmutex);
	if (data->philo_dead == 1)
	{
	//pthread_mutex_unlock(&data->proc);
		pthread_mutex_unlock(&data->write_mutex);
		pthread_mutex_unlock(&data->maymunmutex);
		return (1);
	}
	//pthread_mutex_unlock(&data->proc);
	pthread_mutex_unlock(&data->maymunmutex);
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
	smart_sleep(data->time_to_sleep);
	return (0);
}
