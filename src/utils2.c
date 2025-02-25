/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:51:44 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 20:57:50 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// get_maxf gets the maximum value between two floats
float	get_maxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

// get_minf gets the minimum value between two floats
float	get_minf(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

// get_maxi gets the maximum value between two integers
int	get_maxi(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

// get_mini gets the minimum value between two integers
int	get_mini(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
