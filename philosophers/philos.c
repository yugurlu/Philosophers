/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:41 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/03 18:37:56 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	data->thread_index = 0;
}

void	*one_philo(void *void_data)
{
	t_data	*data;

	data = (t_data *)void_data;
	data->start_time = get_time();
	print_action(data, 0, "has taken a fork", BLUE);
	smart_sleep(data->time_to_die);
	print_action(data, 0, "died", RED);
	destroy(data);
	return (NULL);
}

int	philo_dead(t_data *data, int index)
{
	unsigned long	time;

	pthread_mutex_lock(&data->proc);
	time = get_passed_time(data->philo[index].last_eat);
	if (data->philo[index].meals == data->philo[index].num_must_meals)
	{
		pthread_detach(data->philo[index].thread);
		pthread_mutex_unlock(&data->proc);
		return (1);
	}
	if (time > (unsigned long)data->time_to_die)
	{
		pthread_mutex_unlock(&data->proc);
		print_action(data, index, "died", RED);
		pthread_mutex_lock(&data->proc);
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->proc);
		return (1);
	}
	pthread_mutex_unlock(&data->proc);
	return (0);
}

void	*dead(void *void_data)
{
	int		index;
	t_data	*data;

	data = (t_data *)void_data;
	while (1)
	{
		index = 0;
		pthread_mutex_lock(&data->proc);
		if (data->philo_dead == 1)
		{
			printf("girdim");
			pthread_mutex_unlock(&data->proc);
			return (NULL);
		}
		if (data->num_must_eat != -1)
		{
			if (data->total_num_must_eat == data->total_meals)
			{
				printf("girdim kanka");
				pthread_mutex_unlock(&data->proc);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&data->proc);
		while (index < data->num_philo)
		{
			if (philo_dead(data, index) == 1)
				break ;
			index++;
		}
	}
	return (NULL);
}
