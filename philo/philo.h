/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugurlu <yugurlu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:23:14 by yugurlu           #+#    #+#             */
/*   Updated: 2023/02/04 11:09:45 by yugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\e[31m"
# define BLUE "\e[34m"
# define GREEN "\e[32m"

typedef struct s_philo
{
	int				philo_id;
	int				meals;
	int				num_must_meals;
	unsigned long	last_eat;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				philo_dead;
	int				thread_index;
	unsigned long	start_time;
	pthread_t		dead;
	pthread_mutex_t	proc;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}					t_data;

unsigned long		get_time(void);
void				smart_sleep(int time);
void				destroy(t_data *data);
void				*dead(void *void_data);
int					ft_atoi(const char *str);
void				philo_init(t_data *data);
void				mutex_init(t_data *data);
void				thread_init(t_data *data);
void				*routine(void *void_data);
void				join_threads(t_data *data);
int					control(int ac, char **arg);
void				*one_philo(void *void_data);
int					eating(t_data *data, int index);
int					routinee(t_data *data, int index);
int					get_data(t_data *data, char **av);
int					thinking(t_data *data, int index);
int					sleeping(t_data *data, int index);
unsigned long		get_passed_time(unsigned long begin);
int					print_action(t_data *data, int index, char *str,
						char *color);

#endif
