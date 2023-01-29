/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:45:53 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/29 19:19:04 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	control(int ac, char **arg)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments!\n");
		return (1);
	}
	while (arg[j])
	{
		while (arg[j][i])
		{
			if (arg[j][i] < '0' || arg[j][i] > '9')
			{
				printf("Error: Wrong argument!\n");
				return (1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	i = 0;
	pthread_mutex_destroy(&data->write_mutex);
	free(data->forks);
	free(data->philo);
}

unsigned long	get_passed_time(unsigned long begin)
{
	return (get_time() - begin);
}

void	smart_sleep(int time)
{
	unsigned long	begin;

	begin = get_time();
	while (get_passed_time(begin) <= (unsigned long)time)
		usleep(100);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}
