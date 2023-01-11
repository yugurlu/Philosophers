/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:52:38 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/11 16:52:56 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_data(t_data *data, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->num_must_eat = ft_atoi(av[5]);
	else
		data->num_must_eat = -1;
}

void	info(t_data *data)
{
	int	i;

	i = 0;
}

void	creat_thread(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->num_philo);
	while (i < data->num_philo)
		pthread_create(&threads[i++], NULL, info, data);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*threads;

	if (ac < 5 && ac > 6)
	{
		printf("Wrong number of arguments!\n");
		return (0);
	}
	data = (t_data *)malloc(sizeof(t_data));
	get_data(data, av);
	create_thread(data, threads);
	pthread_mutex_init(&data->mutex, NULL);
}
