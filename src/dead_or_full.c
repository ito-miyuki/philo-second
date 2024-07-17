/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_or_full.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:08:31 by mito              #+#    #+#             */
/*   Updated: 2024/07/17 17:15:44 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->all_meals_eaten == true)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	is_anyone_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->dead_flag == true)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

static int	is_everyone_full(t_data *data)
{
	pthread_mutex_lock(&data->full_lock);
	if (data->full_flag == true)
	{
		pthread_mutex_unlock(&data->full_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->full_lock);
	return (0);
}


int	dead_or_full(t_data *data)
{
	if (is_anyone_dead(data) || is_everyone_full(data))
		return (1);
	else
		return (0);
}
