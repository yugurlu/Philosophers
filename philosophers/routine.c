/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:08:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/01 14:02:43 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *void_data)
{
	int		index;
	t_data	*data;

	data = (t_data *)void_data;
	pthread_mutex_lock(&data->proc2);
	index = data->thread_index;
	pthread_mutex_unlock(&data->proc2);
	while (1)
	{
		pthread_mutex_lock(&data->proc);
		if (data->philo_dead == 1)
		{
			pthread_mutex_unlock(&data->proc);
			break ;
		}
		pthread_mutex_unlock(&data->proc);
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
	if (print_action(data, index, "has taken a fork", BLUE) == 1)
		return (1);
	pthread_mutex_lock(&data->forks[(index + 1) % data->num_philo]);
	if (print_action(data, index, "has taken a fork", BLUE) == 1)
		return (1);
	if (print_action(data, index, "is eating", GREEN) == 1)
		return (1);
	pthread_mutex_lock(&data->proc2);
	data->philo[index].meals++;
	data->total_num_must_eat++;
	data->philo[index].last_eat = get_time();
	pthread_mutex_unlock(&data->proc2);
	smart_sleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % data->num_philo]);
	return (0);
}

int	thinking(t_data *data, int index)
{
	if (print_action(data, index, "is thinking", BLUE) == 1)
		return (1);
	return (0);
}

int	sleeping(t_data *data, int index)
{
	if (print_action(data, index, "is sleeping", BLUE) == 1)
		return (1);
	smart_sleep(data->time_to_sleep);
	return (0);
}

int	print_action(t_data *data, int index, char *str, char *color)
{
	long long	time;

	pthread_mutex_lock(&data->proc);
	pthread_mutex_lock(&data->write_mutex);
	if (data->num_must_eat == data->philo[index].meals)
	{
		pthread_mutex_unlock(&data->proc);
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->proc);
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	time = get_passed_time(data->start_time);
	printf("%s%-10lld   %d %s\n", color, time, data->philo[index].philo_id,
			str);
	pthread_mutex_unlock(&data->write_mutex);
	pthread_mutex_unlock(&data->proc);
	return (0);
}
