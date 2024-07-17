/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:58:53 by mito              #+#    #+#             */
/*   Updated: 2024/07/15 15:56:01 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (!(is_valid_args(argc, argv)))
		return (1);
	if (init_data(&data, argv) != 0)
		return (destroy_data_mutexes(&data));
	philo = malloc(sizeof(t_philo) * data.num_of_philos);
	if (!philo)
	{
		ft_putendl_fd("malloc failed", 2);
		return (destroy_data_mutexes(&data));
	}
	if (init_philo(philo, &data) != 0)
		return (clean_up(&data, philo), 1);
	if (create_threads(philo, &data) != 0)
		return (clean_up(&data, philo), 1);
	clean_up(&data, philo);
	return (0);
}
