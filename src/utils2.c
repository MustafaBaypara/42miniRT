/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:51:44 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/27 17:02:10 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_maxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	get_minf(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

int	get_maxi(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	get_mini(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
