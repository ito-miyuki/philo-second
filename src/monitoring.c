/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:40:00 by mito              #+#    #+#             */
/*   Updated: 2024/07/17 17:08:25 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_dead_yet(t_philo *philo)
{
	size_t	current_time;
	size_t	elapsed_time;

	pthread_mutex_lock(&philo->meal_lock);
	current_time = get_current_time();
	elapsed_time = current_time - philo->last_meal_time;
	if (elapsed_time >= philo->data->time_to_die)
	{
		print_death(philo);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static int	death_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philos || is_anyone_dead(philo->data))
	{
		if (philo_dead_yet(&philo[i]))
		{
			pthread_mutex_lock(&philo->data->death_lock);
			philo->data->dead_flag = true;
			pthread_mutex_unlock(&philo->data->death_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	meal_check(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->num_times_to_eat == -1)
		return (0);
	while (i < philo->data->num_of_philos)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].num_meals_eaten < philo->data->num_times_to_eat)
		{
			pthread_mutex_unlock(&philo[i].meal_lock);
			return (0);
		}
		philo[i].all_meals_eaten = true;
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	pthread_mutex_lock(&philo->data->full_lock);
	philo->data->full_flag = true;
	pthread_mutex_unlock(&philo->data->full_lock);
	return (0);
}

void	*monitoring(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (meal_check(philo) || death_check(philo))
			break ;
	}
	pthread_mutex_lock(&philo->data->write_lock);
	philo->data->can_write = false;
	pthread_mutex_unlock(&philo->data->write_lock);
	return (NULL);
}
