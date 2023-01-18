/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:23:14 by yugurlu           #+#    #+#             */
/*   Updated: 2023/01/18 21:58:27 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philo_id;
	int				meals;
	int				num_must_meals;
	time_t			time_of_last_meal;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	long long		last_eat;
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
	int				philo_dead;
	int				thread_number;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	t_philo			*philo;
}					t_data;

void				join_threads(t_data *data);
long long			get_time(void);
int	sleeping(t_data *data, int index);
int	print_action(t_data *data,int index, char *str);
void				control(int ac, char **arg);
void				get_data(t_data *data, char **av);
int					eating(t_data *data, int index);

#endif
