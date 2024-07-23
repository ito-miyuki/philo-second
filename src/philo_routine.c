/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:58:29 by mito              #+#    #+#             */
/*   Updated: 2024/07/23 13:22:20 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dinner_for_one(t_philo *philo)
{
	ft_usleep(philo->data->time_to_sleep, philo);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	if (dead_or_full(philo) == 1)
		return (1);
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (dead_or_full(philo) == 1)
		return (1);
	print_action(philo, "is thinking");
	return (0);
}

static int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	if (philo->data->num_of_philos == 1)
		return (dinner_for_one(philo));
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	if (dead_or_full(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->meal_lock);
	print_action(philo, "is eating");
	philo->last_meal_time = get_current_time();
	philo->num_meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	if (philo->philo_index % 2 == 1)
	{
		thinking(philo);
		ft_usleep(philo->data->time_to_eat / 2, philo);
	}
	while (!dead_or_full(philo))
	{
		if (eating(philo) == 1)
			return (NULL);
		if (sleeping(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
