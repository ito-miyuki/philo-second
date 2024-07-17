/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:15:32 by mito              #+#    #+#             */
/*   Updated: 2024/07/16 14:04:26 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i].data = data;
		philo[i].philo_index = i + 1;
		philo[i].right_fork = &data->forks[i];
		philo[i].num_meals_eaten = 0;
		if (i == (data->num_of_philos - 1))
			philo[i].left_fork = &data->forks[0];
		else
			philo[i].left_fork = &data->forks[i + 1];
		philo[i].last_meal_time = philo->data->start_time;
		philo[i].all_meals_eaten = false;
		if (pthread_mutex_init(&philo[i].meal_lock, NULL) != 0)
		{
			philo[i].meal_lock_initialized = 0;
			return (1);
		}
		philo[i].meal_lock_initialized = 1;
		i++;
	}
	return (0);
}
