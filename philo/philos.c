/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:41 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/12 13:17:43 by yugurlu          ###   ########.fr       */
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
	print_action(data, 0, "has taken a fork", BLUE);
	smart_sleep(data->time_to_die);
	printf("%s%-10lu   %d %s\n", RED,
		get_passed_time(data->start_time), data->philo[0].philo_id,
		"died");
	return (NULL);
}

int	philo_dead(t_data *data, int index)
{
	unsigned long	time;

	pthread_mutex_lock(&data->write_mutex);
	time = get_passed_time(data->philo[index].last_eat);
	if (time >= (unsigned long)data->time_to_die)
	{
		printf("%s%-10lu   %d %s\n", RED, time, data->philo[index].philo_id,
			"died");
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}

void	*dead(void *void_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)void_data;
	while (1)
	{
		i = 0;
		if (!is_dead(data) || !all_philos_eat(data))
			break ;
		while (i < data->num_philo)
		{
			if (!all_philos_eat(data) || philo_dead(data, i))
				break ;
			i++;
		}
	}
	return (NULL);
}
