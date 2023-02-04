/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:04:42 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/04 10:18:32 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		pn;
	long	result;

	i = 0;
	pn = 1;
	result = 0;
	while (str[i] == 32 || ((str[i] >= 9) && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pn *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0') * pn;
		if (result > 2147483647)
			return (-1);
		if (result < -2147483648)
			return (0);
		i++;
	}
	return ((int)result);
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
		usleep(10);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}
