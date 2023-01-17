/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:23:14 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/17 16:19:00 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philo_id;
	int				meals;
	int				total_meals;
	time_t			time_of_last_meal;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				last_meal;
	time_t			limit_of_life;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	struct s_arg	*arg;
}					t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				start_time;
	int				nbr_of_meals;
	int				philo_dead;
	int				thread_number;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	t_philo			*philo;
}					t_data;

void				control(int ac, char **arg);
void				get_data(t_data *data, char **av);
int					eat(t_data *data);

#endif
