/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:58:56 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 20:12:49 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// new_vec3 creates a new vector with the given x, y, and z values
t_vector3	new_vec3(double x, double y, double z)
{
	t_vector3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

// distance calculates the distance between two vectors
double	distance(t_vector3 a, t_vector3 b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)));
}

// dot_pd calculates the dot product of two vectors which is the sum of the products of the corresponding elements of the two sequences of numbers
double	dot_pd(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// vec3_minus subtracts the given vector from the origin which is used for the direction of the ray
t_vector3	vec3_minus(t_vector3 v1)
{
	return (new_vec3(-v1.x, -v1.y, -v1.z));
}
