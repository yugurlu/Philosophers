/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:08:52 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/03 18:39:44 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *void_data)
{
	int		index;
	t_data	*data;

	data = (t_data *)void_data;
	index = data->thread_index;
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
	pthread_mutex_lock(&data->proc);
	data->philo[index].meals++;
	data->total_meals++;
	data->philo[index].last_eat = get_time();
	pthread_mutex_unlock(&data->proc);
	smart_sleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % data->num_philo]);
	//printf("\n%d  %d  %d -> %d\n",data->philo[index].philo_id, data->philo[index].meals,data->total_meals, data->total_num_must_eat);
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
	unsigned long	time;

	pthread_mutex_lock(&data->write_mutex);
	pthread_mutex_lock(&data->proc);
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
	printf("%s%-10lu   %d %s\n", color, time, data->philo[index].philo_id, str);
	pthread_mutex_unlock(&data->proc);
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}
