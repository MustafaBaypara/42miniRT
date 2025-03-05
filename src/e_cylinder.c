/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:33:19 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/05 17:33:34 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	cylinder_intersection(t_ray ray, t_cylinder cyl, int *is_side)
{
	double	cy_inter;
	double	cap_inter;

	cy_inter = isec_side(ray, cyl);
	cap_inter = isec_cap(ray, cyl, 0, 0);
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
	else if (t > 1)
		t = 1;
	return (vec3_add(A, vec3_mult(a_b, t)));
}

static void	init_imp(t_impact *imp, double tmp, t_cylinder *cyl, t_ray r)
{
	imp->distance = tmp;
	imp->point = vec3_add(r.origin, vec3_mult(r.dir, tmp));
	imp->normal = cyl->dir;
}

void	cyl_ray(t_ray r, t_scene *sc, t_impact *imp, void **objs)
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
		tmp = cylinder_intersection(r, *cyl, &is_side);
		if (tmp < imp->distance && tmp > 0)
		{
			*objs = cyl;
			init_imp(imp, tmp, cyl, r);
			if (is_side)
				imp->normal = vec3_norm(vec3_sub(imp->point,
							closest_point(cyl->pos, vec3_add(cyl->pos,
									vec3_mult(cyl->dir, cyl->height)),
								imp->point)));
			imp->normal = vec3_norm(imp->normal);
			imp->object = "cy";
		}
		lst = lst->next;
	}
}
