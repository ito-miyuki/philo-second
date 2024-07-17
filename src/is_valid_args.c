/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:54:34 by mito              #+#    #+#             */
/*   Updated: 2024/07/15 15:54:50 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}

static int	check_value(char *argv)
{
	if (!(is_digit_str(argv)))
	{
		ft_putendl_fd("Error: Arguments can only contain digits", 2);
		return (-1);
	}
	if (ft_atoi(argv) < 0)
	{
		ft_putendl_fd("Error: Arguments must be positive numbers", 2);
		return (-1);
	}
	return (0);
}

int	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Error: Invalid number of arguments.", 2);
		return (0);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		ft_putendl_fd("Error: At least 1 philosopher is required.", 2);
		return (0);
	}
	while (argv[i] != NULL)
	{
		if (check_value(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}
