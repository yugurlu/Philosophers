/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:41 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/01 13:57:57 by yugurlu          ###   ########.fr       */
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

int	philo_death(t_data *data, int index)
{
	int	time;

	pthread_mutex_lock(&data->proc2);
	time = get_passed_time(data->philo[index].last_eat);
	if (time > data->time_to_die)
	{
		pthread_mutex_unlock(&data->proc2);
		print_action(data, index, "died", RED);
		pthread_mutex_lock(&data->proc);
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->proc);
		return (1);
	}
	pthread_mutex_unlock(&data->proc2);
	return (0);
}

void	*death(void *void_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)void_data;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->proc);
		if (data->philo_dead == 1)
		{
			pthread_mutex_unlock(&data->proc);
			break ;
		}
		pthread_mutex_unlock(&data->proc);
		pthread_mutex_lock(&data->proc2);
		if (data->total_num_must_eat == data->num_must_eat)
		{
			pthread_mutex_unlock(&data->proc2);
			break ;
		}
		pthread_mutex_unlock(&data->proc2);
		while (i < data->num_philo)
		{
			if (philo_death(data, i) == 1)
			{
				destroy(data);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
