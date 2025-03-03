/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:30:29 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/03 15:08:11 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// solve_pl calculates the intersection of the ray and the plane
double	solve_pl(t_vector3 origin, t_vector3 dir, t_vector3 pos, t_vector3 n)
{
	double	denom;
	double	t;

	denom = dot_pd(n, dir); // get the dot product of the normal of the plane and the direction of the ray
	if (denom == 0) // if the dot product is 0, return INFINITY
		return (INFINITY);
	t = dot_pd(n, vec3_sub(pos, origin)) / denom; // get the distance between the origin of the ray and the point of impact by getting the dot product of the vector from the origin of the ray to the position of the plane and the normal of the plane, then dividing it by the dot product of the normal of the plane and the direction of the ray
	if (t > EPSILON) // if the distance is greater than EPSILON, return the distance
		return (t);
	return (INFINITY); // if the distance is less than EPSILON, return INFINITY
}

int	solve_cyl(double a[2], t_ray ray, t_cylinder cyl)
{
	t_vector3	v;
	t_vector3	u;
	double		i;
	double		j;
	double		k;
	// ray direction perpendicular to the cylinder axis.
	v = vec3_mult(cyl.dir, dot_pd(ray.dir, cyl.dir));
	v = vec3_sub(ray.dir, v);
	// Vector from cylinder axis to ray origin, perpendicular to axis.
	u = vec3_mult(cyl.dir, dot_pd(vec3_sub(ray.origin, cyl.pos), cyl.dir));
	u = vec3_sub(vec3_sub(ray.origin, cyl.pos), u);
	// calculate the coefficients of the quadratic equation
	i = dot_pd(v, v);
	j = 2 * dot_pd(v, u);
	k = dot_pd(u, u) - pow(cyl.radius, 2);
	// i * t^2 + j * t + k = 0
	// t = (-j ± √(j^2 - 4ik)) / (2i)
	a[0] = (-j + sqrt(pow(j, 2) - 4 * i * k)) / (2 * i);
	a[1] = (-j - sqrt(pow(j, 2) - 4 * i * k)) / (2 * i);
	// if the discriminant is less than 0, return 0 which means the ray does not hit the cylinder
	if (a[0] < EPSILON && a[1] < EPSILON)
		return (0);
	return (1);
}

// calc_normal calculates the normal of the cylinder
void	calc_normal(double a[2], t_cylinder cyl, double d1, double d2)
{
	double	i;

	if ((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
		&& (d2 >= 0 && d2 <= cyl.height && a[1] > EPSILON)) // if the dot product is between 0 and the height of the cylinder and the distance is less than EPSILON
	{
		i = a[1]; // set i to a[1]
		if (a[0] < a[1]) // if a[0] is less than a[1], set i to a[0]
			i = a[0];
	}
	else if (d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON) // if the dot product is between 0 and the height of the cylinder and the distance is less than EPSILON
		i = a[0];
	else
		i = a[1];
	a[0] = i;
}


double	isec_cap(t_ray ray, t_cylinder cyl, double d1, double d2)
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	cap;

	// get the position of the top cap
	cap = vec3_add(cyl.pos, vec3_mult(cyl.dir, cyl.height));
	// get the distance between the origin of the ray and the base cap
	d1 = solve_pl(ray.origin, ray.dir, cyl.pos, cyl.dir);
	// get the distance between the origin of the ray and the top cap
	d2 = solve_pl(ray.origin, ray.dir, cap, cyl.dir);
	// if both d1 and d2 are less than INFINITY which means the ray intersects the base and top cap
	if (d1 < INFINITY && d2 < INFINITY)
	{
		// get the point of hit on the base and top cap
		p1 = vec3_add(ray.origin, vec3_mult(ray.dir, d1));
		p2 = vec3_add(ray.origin, vec3_mult(ray.dir, d2));
		// checks if the hit points p1 and p2 are within the circular caps
		// if they are, return the minimum distance between the base and top cap
		if ((d1 < INFINITY && distance(p1, cyl.pos) <= cyl.radius)
			&& (d2 < INFINITY && distance(p2, cap) <= cyl.radius))
			return (get_minf(d1, d2));
		// if the hit point p1 is within the base cap, return the distance between the origin of the ray and the base cap
		else if (d1 < INFINITY && distance(p1, cyl.pos) <= cyl.radius)
			return (d1);
		// if the hit point p2 is within the top cap, return the distance between the origin of the ray and the top cap
		else if (d2 < INFINITY && distance(p2, cap) <= cyl.radius)
			return (d2);
	}
	// if neither the base cap nor the top cap is hit, return INFINITY
	return (INFINITY);
}


double	isec_side(t_ray ray, t_cylinder cyl)
{
	double	a[2];
	double	d1;
	double	d2;

	if (!solve_cyl(a, ray, cyl))
		return (INFINITY);
	d1 = dot_pd(cyl.dir, vec3_sub(vec3_mult(ray.dir, a[0]),
				vec3_sub(cyl.pos, ray.origin)));
	d2 = dot_pd(cyl.dir, vec3_sub(vec3_mult(ray.dir, a[1]),
				vec3_sub(cyl.pos, ray.origin)));
	if (!((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
			|| (d2 >= 0 && d2 <= cyl.height && a[0] > EPSILON)))
		return (INFINITY);
	calc_normal(a, cyl, d1, d2);
	return (a[0]);
}
