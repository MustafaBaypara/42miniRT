/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:33:19 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/03 19:06:25 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	intersection_side(t_ray ray, t_cylinder cyl)
{
	double	a[2];
	double	d1;
	double	d2;

	if (!solve_cyl(a, ray, cyl))
		return (INFINITY);
	d1 = dot_pd(cyl.direction, vec3_sub(vec3_mult(ray.dir, a[0]),
				vec3_sub(cyl.position, ray.origin)));
	d2 = dot_pd(cyl.direction, vec3_sub(vec3_mult(ray.dir, a[1]),
				vec3_sub(cyl.position, ray.origin)));
	if (!((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
			|| (d2 >= 0 && d2 <= cyl.height && a[0] > EPSILON)))
		return (INFINITY);
	calc_normal(a, cyl, d1, d2);
	return (a[0]);
}

static double	cylinder_intersection(t_ray ray, t_cylinder cyl, int *is_side)
{
	double	cy_inter;
	double	cap_inter;

	cy_inter = intersection_side(ray, cyl);
	if (!cyl.is_closed)
		cap_inter = INFINITY;
	else
		cap_inter = intersection_cap(ray, cyl, is_side);
	if (cy_inter < INFINITY || cap_inter < INFINITY)
	{
		if (cy_inter < cap_inter)
			return (*is_side = 1, cy_inter);
		return (cap_inter);
	}
	return (INFINITY);
}

static t_vector3	closest_point(t_vector3 A, t_vector3 B, t_vector3 P)
{
	t_vector3	a_p;
	t_vector3	a_b;
	double		ab2;
	double		ap;
	double		t;

	a_b = vec3_sub(B, A);
	ab2 = dot_pd(a_b, a_b);
	a_p = vec3_sub(P, A);
	ap = dot_pd(a_p, a_b);
	t = ap / ab2;
	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	return (vec3_add(A, vec3_mult(a_b, t)));
}

void	cylinder_ray(t_ray ray, t_scene *sc, t_impact *imp, void **objs)
{
	t_list		*lst;
	t_cylinder	*cyl;
	double		tmp;
	int			is_side;

	lst = sc->cylinders;
	while (lst->next)
	{
		is_side = 0;
		cyl = (t_cylinder *)lst->content;
		tmp = cylinder_intersection(ray, *cyl, &is_side);
		if (tmp < imp->distance && tmp > 0)
		{
			*objs = cyl;
			imp->distance = tmp;
			imp->point = new_vec3(tmp * ray.dir.x, tmp * ray.dir.y, tmp * ray.dir.z);
			imp->normal = cyl->direction;
			if (is_side)
				imp->normal = vec3_sub(closest_point(cyl->position,
							cyl->position2, imp->point), imp->point);
			imp->normal = vec3_norm(imp->normal);
			imp->object = "cy";
		}
		lst = lst->next;
	}
}
