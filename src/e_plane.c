/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:18:30 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 20:10:56 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static int	plane_intersection(t_ray ray, t_plane plane, t_impact *impact)
{
	double	denom;
	double	t;

	denom = dot_pd(plane.normal, ray.dir); // get the dot product of the normal of the plane and the direction of the ray
	if (fabs(denom) > EPSILON) // if the absolute value of the dot product is greater than EPSILON (a.k.a. 0.000001), then the ray is not parallel to the plane
	{
		t = dot_pd(vec3_sub(plane.pos, ray.origin), plane.normal) / denom; // get the distance between the origin of the ray and the point of impact by getting the dot product of the vector from the origin of the ray to the position of the plane and the normal of the plane, then dividing it by the dot product of the normal of the plane and the direction of the ray
		if (t > EPSILON && t < impact->distance) // if the distance is greater than EPSILON and less than the distance of the impact, update the impact
		{
			impact->distance = t; // update the distance
			if (denom < 0) // if the dot product is less than 0, set the normal to the normal of the plane
				impact->normal = vec3_norm(plane.normal);
			else
				impact->normal = vec3_norm(vec3_mult(plane.normal, -1)); // if the dot product is greater than 0, set the normal to the negative of the normal of the plane
			impact->point = vec3_add(ray.origin, vec3_mult(ray.dir, t)); // get the point of impact
			impact->point = vec3_add(impact->point,
					vec3_mult(impact->normal, EPSILON)); // add EPSILON to the point of impact
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
		if (plane_intersection(ray, *plane, impact)) // check if the ray hits the plane. If it does, update the impact
		{
			*obj = plane;
			impact->object = "pl"; // set the object to plane
		}
		lst = lst->next;
	}
}
