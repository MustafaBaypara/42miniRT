/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:54:43 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/11 18:00:13 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	quadratic_solver(t_vector3 point, double *a, double *b)
{
	double	discriminant;
	double	q;

	discriminant = point.y * point.y - 4 * point.x * point.z;
	if (discriminant < 0)
		return (0);
	else if (discriminant == 0)
	{
		*a = -0.5 * point.y / point.x;
		*b = -0.5 * point.y / point.x;
	}
	else
	{
		q = -0.5 * (point.y - sqrt(discriminant));
		*a = q / point.x;
		*b = point.z / q;
	}
	if (*a > *b)
	{
		q = *a;
		*a = *b;
		*b = q;
	}
	return (1);
}

void	error_exit(char *message, int error_code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(error_code);
}
