/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:52:38 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/17 17:40:03 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*routine(void *void_data)
{
	int i;
	t_data *data;

	data = (t_data *)void_data;
	printf("thread number = %d\n", data->thread_number);
	i = data->thread_number;
	while (data->philo_dead != 1)
	{
		if(eat(data) == 1)
			break;

	}
	return (NULL);
}

void	thread_init(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, data);
		printf("Thread %d created!\n", data->philo[i].philo_id);
		i++;
		data->thread_number++;
		usleep(1000);

	}
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
	int		i;
	t_philo	*philo;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].total_meals = data->nbr_of_meals;
		data->philo[i].meals = 0;
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
	philo_init(data);
	mutex_init(data);
	thread_init(data);
}
