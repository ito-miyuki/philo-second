/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:46:17 by mito              #+#    #+#             */
/*   Updated: 2024/07/16 14:05:08 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_data_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_initialized_forks)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->write_lock_initialized == 1)
		pthread_mutex_destroy(&data->write_lock);
	if (data->death_lock_initialized == 1)
		pthread_mutex_destroy(&data->death_lock);
	if (data->full_lock_initialized == 1)
		pthread_mutex_destroy(&data->full_lock);
	free(data->forks);
	data->forks = NULL;
	return (1);
}

static void	destroy_philo_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philos)
	{
		if (philo[i].meal_lock_initialized == 1)
			pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
}

void	clean_up(t_data *data, t_philo *philo)
{
	destroy_data_mutexes(data);
	destroy_philo_mutexes(philo);
	free(philo);
}
