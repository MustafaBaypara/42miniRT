/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:56:49 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/27 16:57:27 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_vector3 pos, t_vector3 dir)
{
	t_ray	ray;

	ray.origin = pos;
	ray.direction = dir;
	return (ray);
}
