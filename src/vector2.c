/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:54:30 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/05 17:34:18 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_vector3	vec3_norm(t_vector3 v)
{
	double	len;

	len = distance(new_vec3(0, 0, 0), v);
	return (new_vec3(v.x / len, v.y / len, v.z / len));
}

t_vector3	vec3_add(t_vector3 v1, t_vector3 v2)
{
	return (new_vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector3	vec3_sub(t_vector3 v1, t_vector3 v2)
{
	return (new_vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector3	vec3_mult(t_vector3 v, double scalar)
{
	return (new_vec3(v.x * scalar, v.y * scalar, v.z * scalar));
}
