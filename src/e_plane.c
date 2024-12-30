/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:18:30 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/25 14:30:42 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static int	plane_intersection(t_ray ray, t_plane plane, t_impact *impact)
{
	double	denom;
	double	t;

	denom = dot_pd(plane.normal, ray.direction);
	if (fabs(denom) > 0)
	{
		t = dot_pd(vec3_sub(plane.position, ray.origin), plane.normal) / denom;
		if (t > EPSILON && t < impact->distance)
		{
			impact->distance = t;
			impact->normal = vec3_norm(plane.normal);
			impact->point = vec3_add(ray.origin, vec3_mult(ray.direction, t));
			impact->point = vec3_add(impact->point,
					vec3_mult(impact->normal, EPSILON));
			return (1);
		}
	}
	return (0);
}

void	plane_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj)
{
	t_list	*lst;
	t_plane	*plane;

	lst = scene->planes;
	while (lst->next)
	{
		plane = (t_plane *)lst->content;
		if (plane_intersection(ray, *plane, impact))
		{
			*obj = plane;
			impact->object = "pl";
		}
		lst = lst->next;
	}
}
