/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:53:35 by mito              #+#    #+#             */
/*   Updated: 2024/07/17 16:07:13 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (1);
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		data->num_of_initialized_forks++;
		i++;
	}
	return (0);
}

static int	init_mutex(t_data *data)
{
	if (init_forks(data) == 1)
		return (1);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	data->write_lock_initialized = 1;
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (1);
	data->death_lock_initialized = 1;
	if (pthread_mutex_init(&data->full_lock, NULL) != 0)
		return (1);
	data->full_lock_initialized = 1;
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->num_times_to_eat = ft_atoi(argv[5]);
	else
		data->num_times_to_eat = -1;
	data->start_time = get_current_time();
	data->can_write = true;
	data->dead_flag = false;
	data->full_flag = false;
	data->num_of_initialized_forks = 0;
	data->write_lock_initialized = 0;
	data->death_lock_initialized = 0;
	data->full_lock_initialized = 0;
	if (init_mutex(data) != 0)
	{
		ft_putendl_fd("Error initializing mutex", 2);
		return (1);
	}
	return (0);
}
