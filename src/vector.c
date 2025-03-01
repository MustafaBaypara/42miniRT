/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:58:56 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/01 21:45:19 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	new_vec3(double x, double y, double z)
{
	t_vector3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double	distance(t_vector3 a, t_vector3 b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)));
}

double	dot_pd(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	vec3_minus(t_vector3 v1)
{
	return (new_vec3(-v1.x, -v1.y, -v1.z));
}
