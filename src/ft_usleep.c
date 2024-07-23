/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:42:50 by mito              #+#    #+#             */
/*   Updated: 2024/07/15 18:49:58 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milisecs, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milisecs)
	{
		if (dead_flag_check(philo->data))
			return (1);
		usleep(500);
	}
	return (0);
}
