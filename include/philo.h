/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:57:42 by mito              #+#    #+#             */
/*   Updated: 2024/07/17 16:52:09 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h> // are we allowed to use?
# include <sys/time.h> // for gettimeofday function

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	size_t			start_time;
	bool			can_write;
	bool			dead_flag;
	bool			full_flag;
	int				num_of_initialized_forks;
	int				write_lock_initialized;
	int				death_lock_initialized;
	int				full_lock_initialized;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	full_lock;

}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread;
	int				philo_index;
	int				num_meals_eaten;
	size_t			last_meal_time;
	bool			all_meals_eaten;
	int				meal_lock_initialized;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	meal_lock;
}	t_philo;

int		main(int argc, char **argv);
int		is_valid_args(int argc, char **argv);
int		ft_atoi(const char *str);
int		init_data(t_data *data, char **argv);
int		init_philo(t_philo *philo, t_data *data);
int		create_threads(t_philo *philo, t_data *data);
void	*monitoring(void *ptr);
void	*philo_routine(void *ptr);
size_t	get_current_time(void);
void	print_action(t_philo *philo, char *action);
void	print_death(t_philo *philo);
int		dead_or_full(t_data *data);
int		is_philo_dead(t_philo *philo);
int		is_anyone_dead(t_data *data);
void	ft_putendl_fd(char *str, int fd);
int		destroy_data_mutexes(t_data *data);
void	clean_up(t_data *data, t_philo *philo);
int		am_i_full(t_philo *philo);
void	ft_usleep(size_t milisecs);

#endif
