/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:08:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/11 11:37:06 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *void_data)
{
	int		index;
	t_data	*data;

	data = (t_data *)void_data;
	pthread_mutex_lock(&data->write_mutex);
	index = data->thread_index;
	pthread_mutex_unlock(&data->write_mutex);
	while (1)
		if (routinee(data, index))
			break ;
	return (NULL);
}

int	routinee(t_data *data, int index)
{
	if (!is_dead(data))
		return (1);
	if (data->num_must_eat != data->philo[index].meals)
	{
		if (!is_dead(data) || eating(data, index) == 1)
			return (1);
		if (!is_dead(data) || sleeping(data, index) == 1)
			return (1);
		if (!is_dead(data) || thinking(data, index) == 1)
			return (1);
	}
	else
		return (1);
	return (0);
}

int	eating(t_data *data, int index)
{
	if (is_dead(data))
	{
		pthread_mutex_lock(&data->forks[index]);
		if (print_action(data, index, "has taken a fork", BLUE) == 1)
			return (1);
		pthread_mutex_lock(&data->forks[(index + 1) % data->num_philo]);
		if (print_action(data, index, "has taken a fork", BLUE) == 1)
			return (1);
		if (print_action(data, index, "is eating", GREEN) == 1)
			return (1);
		pthread_mutex_lock(&data->write_mutex);
		data->philo[index].meals++;
		data->philo[index].last_eat = get_time();
		pthread_mutex_unlock(&data->write_mutex);
		smart_sleep(data->time_to_eat);
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->num_philo]);
	}
	else
		return (1);
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
