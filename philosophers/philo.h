/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:23:14 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/13 12:52:47 by yugurlu          ###   ########.fr       */
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
	int				nbr_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	time_t			limit_of_life;
	int 			thread;
	int				stop;
	time_t			start_time;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
	int				*forks;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*philo_mutex;
	t_philo			*all_philo;
}					t_data;

#endif
