/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:30:29 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/04 16:05:27 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	solve_pl(t_vector3 origin, t_vector3 dir, t_vector3 pos, t_vector3 n)
{
	double	denom;
	double	t;

	denom = dot_pd(n, dir);
	if (denom == 0)
		return (INFINITY);
	t = dot_pd(n, vec3_sub(pos, origin)) / denom;
	if (t > EPSILON)
		return (t);
	return (INFINITY);
}

int	solve_cyl(double a[2], t_ray ray, t_cylinder cyl)
{
	t_vector3	v;
	t_vector3	u;
	double		i;
	double		j;
	double		k;

	v = vec3_mult(cyl.dir, dot_pd(ray.dir, cyl.dir));
	v = vec3_sub(ray.dir, v);
	u = vec3_mult(cyl.dir, dot_pd(vec3_sub(ray.origin, cyl.pos), cyl.dir));
	u = vec3_sub(vec3_sub(ray.origin, cyl.pos), u);
	i = dot_pd(v, v);
	j = 2 * dot_pd(v, u);
	k = dot_pd(u, u) - pow(cyl.radius, 2);
	a[0] = (-j + sqrt(pow(j, 2) - 4 * i * k)) / (2 * i);
	a[1] = (-j - sqrt(pow(j, 2) - 4 * i * k)) / (2 * i);
	if (a[0] < EPSILON && a[1] < EPSILON)
		return (0);
	return (1);
}

void	calc_normal(double a[2], t_cylinder cyl, double d1, double d2)
{
	double	dist;
	double	i;

	if ((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
		&& (d2 >= 0 && d2 <= cyl.height && a[1] > EPSILON))
	{
		dist = d2;
		i = a[1];
		if (a[0] < a[1])
		{
			dist = d1;
			i = a[0];
		}
	}
	else if (d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
	{
		dist = d1;
		i = a[0];
	}
	else
	{
		dist = d2;
		i = a[1];
	}
	a[0] = dist;
	
	printf("dist: %f\n", dist);
	printf("i: %f\n", i);
	printf("d1: %f\n", d1);
	printf("d2: %f\n", d2);
}
