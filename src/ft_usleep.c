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

void	ft_usleep(size_t milisecs)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milisecs)
		usleep(500);
}
