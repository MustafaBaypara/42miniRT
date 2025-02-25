/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:30:29 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 21:08:38 by abakirca         ###   ########.fr       */
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

// solve_cyl calculates the intersection of the ray and the side of the cylinder
int	solve_cyl(double a[2], t_ray ray, t_cylinder cyl)
{
	t_vector3	v;
	t_vector3	u;
	double		i;
	double		j;
	double		k;

	v = vec3_mult(cyl.dir, dot_pd(ray.dir, cyl.dir)); // get the projection of the direction of the ray on the direction of the cylinder
	v = vec3_sub(ray.dir, v); // get the vector from the projection of the direction of the ray on the direction of the cylinder to the direction of the ray
	u = vec3_mult(cyl.dir, dot_pd(vec3_sub(ray.origin, cyl.pos), cyl.dir)); // get the projection of the vector from the origin of the ray to the position of the cylinder on the direction of the cylinder
	u = vec3_sub(vec3_sub(ray.origin, cyl.pos), u); // get the vector from the projection of the vector from the origin of the ray to the position of the cylinder on the direction of the cylinder to the vector from the origin of the ray to the position of the cylinder
	i = dot_pd(v, v); // get the dot product of the vector from the projection of the direction of the ray on the direction of the cylinder to the direction of the ray
	j = 2 * dot_pd(v, u); // get the dot product of the vector from the projection of the direction of the ray on the direction of the cylinder to the direction of the ray and the vector from the projection of the vector from the origin of the ray to the position of the cylinder on the direction of the cylinder to the vector from the origin of the ray to the position of the cylinder
	k = dot_pd(u, u) - pow(cyl.radius, 2); // get the dot product of the vector from the projection of the vector from the origin of the ray to the position of the cylinder on the direction of the cylinder to the vector from the origin of the ray to the position of the cylinder and the vector from the projection of the vector from the origin of the ray to the position of the cylinder on the direction of the cylinder to the vector from the origin of the ray to the position of the cylinder minus the square of the radius of the cylinder
	a[0] = (-j + sqrt(pow(j, 2) - 4 * i * k)) / (2 * i); // solve the quadratic equation
	a[1] = (-j - sqrt(pow(j, 2) - 4 * i * k)) / (2 * i); // solve the quadratic equation
	if (a[0] < EPSILON && a[1] < EPSILON) // if both a[0] and a[1] are less than EPSILON, return 0
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

// isec_cap calculates the intersection of the ray and the top cap of the cylinder
double	isec_cap(t_ray ray, t_cylinder cyl, double d1, double d2)
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	cap;

	cap = vec3_add(cyl.pos, vec3_mult(cyl.dir, cyl.height)); // get the position of the top cap of the cylinder
	d1 = solve_pl(ray.origin, ray.dir, cyl.pos, cyl.dir); // solve the intersection of the ray and the bottom cap of the cylinder
	d2 = solve_pl(ray.origin, ray.dir, cap, cyl.dir); // solve the intersection of the ray and the top cap of the cylinder
	if (d1 < INFINITY && d2 < INFINITY) // if the distance is less than INFINITY
	{
		p1 = vec3_add(ray.origin, vec3_mult(ray.dir, d1)); // get the point of impact
		p2 = vec3_add(ray.origin, vec3_mult(ray.dir, d2)); // get the point of impact
		if ((d1 < INFINITY && distance(p1, cyl.pos) <= cyl.radius)
			&& (d2 < INFINITY && distance(p2, cap) <= cyl.radius)) // if the distance is less than INFINITY and the distance between the point of impact and the position of the cap is less than the radius of the cylinder
			return (get_minf(d1, d2)); // return the minimum value between d1 and d2
		else if (d1 < INFINITY && distance(p1, cyl.pos) <= cyl.radius) // if the distance is less than INFINITY and the distance between the point of impact and the position of the cap is less than the radius of the cylinder
			return (d1); // return d1
		else if (d2 < INFINITY && distance(p2, cap) <= cyl.radius) // if the distance is less than INFINITY and the distance between the point of impact and the position of the cap is less than the radius of the cylinder
			return (d2); // return d2
	}
	return (INFINITY); // if the distance is greater than INFINITY, return INFINITY
}

// isec_side calculates the intersection of the ray and the side of the cylinder
double	isec_side(t_ray ray, t_cylinder cyl)
{
	double	a[2];
	double	d1;
	double	d2;

	if (!solve_cyl(a, ray, cyl)) // check if the ray hits the side of the cylinder
		return (INFINITY);
	d1 = dot_pd(cyl.dir, vec3_sub(vec3_mult(ray.dir, a[0]),
				vec3_sub(cyl.pos, ray.origin))); // get the dot product of the direction of the cylinder and the vector from the origin of the ray to the point of impact
	d2 = dot_pd(cyl.dir, vec3_sub(vec3_mult(ray.dir, a[1]),
				vec3_sub(cyl.pos, ray.origin))); // get the dot product of the direction of the cylinder and the vector from the origin of the ray to the point of impact
	if (!((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
			|| (d2 >= 0 && d2 <= cyl.height && a[0] > EPSILON))) // if the dot product is not between 0 and the height of the cylinder and the distance is less than EPSILON
		return (INFINITY);
	calc_normal(a, cyl, d1, d2); // calculate the normal of the cylinder
	return (a[0]); // return the distance
}
