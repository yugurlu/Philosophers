/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:08:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/18 21:58:57 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_data *data, int index)
{
	pthread_mutex_lock(&data->philo[index].left_fork);
	if (print_action(data, index, "has taken a fork") == 1)
		return (1);
	pthread_mutex_lock(&data->philo[index].right_fork);
	if (print_action(data, index, "has taken a fork") == 1)
		return (1);
	if (print_action(data, index, "is eating") == 1)
		return (1);
	data->philo[index].meals++;
	data->philo[index].last_eat = get_time();
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->philo[index].left_fork);
	pthread_mutex_unlock(&data->philo[index].right_fork);
	return (0);
}

int	print_action(t_data *data, int index, char *str)
{
	long long	time;

	time = get_time() - data->start_time;
	pthread_mutex_lock(&data->write_mutex);
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	printf("%d %s\n", data->philo[index].philo_id, str);
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}

int	sleeping(t_data *data, int index)
{
	if (print_action(data, index, "is sleeping") == 1)
		return (1);
	usleep(data->time_to_sleep * 1000);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001)); //return time in milliseconds
}
