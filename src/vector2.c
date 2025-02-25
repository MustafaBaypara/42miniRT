/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:54:30 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 20:51:58 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

//vec3_norm calculates the normalized vector of the given vector
t_vector3	vec3_norm(t_vector3 v)
{
	double	len;

	len = distance(new_vec3(0, 0, 0), v);
	return (new_vec3(v.x / len, v.y / len, v.z / len));
}

//vec3_add adds two vectors
t_vector3	vec3_add(t_vector3 v1, t_vector3 v2)
{
	return (new_vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

//vec3_sub subtracts two vectors
t_vector3	vec3_sub(t_vector3 v1, t_vector3 v2)
{
	return (new_vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

//vec3_mult multiplies a vector by a scalar
t_vector3	vec3_mult(t_vector3 v, double scalar)
{
	return (new_vec3(v.x * scalar, v.y * scalar, v.z * scalar));
}
