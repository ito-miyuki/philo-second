/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:53:04 by mito              #+#    #+#             */
/*   Updated: 2024/07/15 15:45:33 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(pthread_t monitor, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(monitor, NULL) != 0)
	{
		ft_putendl_fd("Error joining monitor thread", 2);
		return (1);
	}
	while (i < data->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			ft_putendl_fd("Error joining philo threads", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_philo *philo, t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, philo) != 0)
	{
		ft_putendl_fd("Error creating monitor thread\n", 2);
		return (1);
	}
	while (i < data->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i])
			!= 0)
		{
			ft_putendl_fd("Error creating monitor thread\n", 2);
			return (1);
		}
		i++;
	}
	if (join_threads(monitor, philo, data) != 0)
		return (1);
	return (0);
}
