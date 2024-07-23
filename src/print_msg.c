/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:00:03 by mito              #+#    #+#             */
/*   Updated: 2024/07/17 17:06:16 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = (get_current_time() - philo->data->start_time);
	printf("%d %d died\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_action(t_philo *philo, char *action)
{
	int	timestamp;

	if (dead_flag_check(philo->data) == 1)
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = (get_current_time() - philo->data->start_time);
	if (philo->data->can_write == true || dead_flag_check(philo->data) == 0)
		printf("%d %d %s\n", timestamp, philo->philo_index, action);
	pthread_mutex_unlock(&philo->data->write_lock);
}
