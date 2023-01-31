/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:52:38 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/31 15:01:52 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (control(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (get_data(data, av))
		return (1);
	mutex_init(data);
	philo_init(data);
	thread_init(data);
	destroy(data);
	return (0);
}
