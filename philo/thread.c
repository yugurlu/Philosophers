/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:46:07 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/10 15:02:28 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_init(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_philo == 1)
	{
		pthread_create(&data->philo[0].thread, NULL, &one_philo, data);
		pthread_join(data->philo[0].thread, NULL);
		return ;
	}
	else
	{
		data->start_time = get_time();
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->write_mutex);
			data->thread_index = i;
			pthread_mutex_unlock(&data->write_mutex);
			pthread_create(&data->philo[i++].thread, NULL, &routine, data);
			usleep(100);
		}
		pthread_create(&data->dead, NULL, &dead, data);
		join_threads(data);
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_join(data->philo[i++].thread, NULL);
	pthread_join(data->dead, NULL);
}

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
}

int	print_action(t_data *data, int index, char *str, char *color)
{
	unsigned long	time;

	pthread_mutex_lock(&data->write_mutex);
	if (data->num_must_eat == data->philo[index].meals)
	{
		pthread_mutex_unlock(&data->write_mutex);
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->num_philo]);
		return (1);
	}
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->write_mutex);
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->num_philo]);
		return (1);
	}
	time = get_passed_time(data->start_time);
	printf("%s%-10lu   %d %s\n", color, time, data->philo[index].philo_id, str);
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}
