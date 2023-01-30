/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:46:07 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/30 16:30:00 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_init(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	if (data->num_philo == 1)
	{
		one_philo(data);
		return ;
	}
	else
	{
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->proc);
			data->thread_number = i;
			pthread_mutex_unlock(&data->proc);
			pthread_create(&data->philo[i++].thread, NULL, &routine, data);
			usleep(1);
		}
	}
	death(data);
	join_threads(data);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_join(data->philo[i++].thread, NULL);
}

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->proc, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
}