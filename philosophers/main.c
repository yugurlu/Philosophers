/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:52:38 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/12 20:35:05 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	control(int ac, char **arg)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments!\n");
		exit(1);
	}
	while (arg[j])
	{
		while (arg[j][i])
		{
			if (arg[j][i] < '0' || arg[j][i] > '9')
			{
				printf("Error: Wrong argument!\n");
				exit(1);
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	get_data(t_data *data, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		if (ft_atoi(av[5]) < 1)
		{
			printf("Error: Wrong argument!\n");
			//free
			exit(1);
		}
		data->nbr_of_meals = ft_atoi(av[5]);
	}
	else
	{
		if (data->num_philo < 1)
		{
			printf("Error: Wrong argument!\n");
			//free
			exit(1);
		}
		data->nbr_of_meals = -1;
	}
}

void	mutex_init(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->forks = forks;
}

t_philo	*philo_init(t_data *data)
{
	int i;
	t_philo		*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->num_philo);
	while (i < data->num_philo)
	{
		philo[i].philo_id = i;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].time_to_die = data->time_to_die;
		philo[i].meals = 0;
		philo[i].total_meals = data->nbr_of_meals;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		i++;
	}
	data->all_philo = philo;

}

void	thread_init(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
		pthread_create(&data->all_philo[i].thread, NULL, /**&dinner*/ &data->all_philo[i++]);
}

int main(int ac, char **av)
{
	t_data	*data;

	control(ac, av);
	data = (t_data *)malloc(sizeof(t_data));
	get_data(data, av);
	mutex_init(data);
	philo_init(data);
	thread_init(data);
}
