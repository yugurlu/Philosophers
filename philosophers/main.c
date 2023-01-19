/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:52:38 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/19 20:32:37 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *void_data)
{
	int		index;
	t_data	*data;

	data = (t_data *)void_data;
	index = data->thread_number;
	while (data->philo_dead != 1)
	{
		if (eating(data, index) == 1)
			break ;
		if (data->num_must_eat != data->philo[data->thread_number].meals)
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

void	thread_init(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philo)
	{
		data->thread_number = i;
		pthread_create(&data->philo[i++].thread, NULL, &routine, data);
		usleep(1000);
	}
	pthread_create(&data->death, NULL, &death, data);
	usleep(1000);
	join_threads(data);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_join(data->philo[i++].thread, NULL);
	pthread_join(data->death, NULL);
}

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
}

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
		data->philo[i].left_fork = data->forks[i];
		data->philo[i].right_fork = data->forks[(i + 1) % data->num_philo];
		i++;
	}
	data->philo_dead = 0;
	data->thread_number = 0;
}

int	main(int ac, char **av)
{
	t_data	*data;

	control(ac, av);
	data = (t_data *)malloc(sizeof(t_data));
	get_data(data, av);
	mutex_init(data);
	philo_init(data);
	thread_init(data);
}
