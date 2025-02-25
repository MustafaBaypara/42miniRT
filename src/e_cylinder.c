/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:33:19 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 21:05:58 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	cylinder_intersection(t_ray ray, t_cylinder cyl, int *is_side)
{
	double	cy_inter;
	double	cap_inter;

	cy_inter = isec_side(ray, cyl); // check if the ray hits the side of the cylinder
	cap_inter = isec_cap(ray, cyl, 0, 0); // check if the ray hits the top cap of the cylinder
	if (cy_inter < INFINITY || cap_inter < INFINITY) // if the ray hits the side or the top cap of the cylinder
	{
		if (cy_inter < cap_inter) // if the ray hits the side of the cylinder
			return (*is_side = 1, cy_inter); // return the side intersection
		return (cap_inter); // if the ray hits the top cap of the cylinder, return the top cap intersection
	}
	return (INFINITY); // if the ray does not hit the cylinder, return INFINITY
}

// closest_point gets the closest point on the cylinder to the point of impact
static t_vector3	closest_point(t_vector3 A, t_vector3 B, t_vector3 P)
{
	t_vector3	a_p;
	t_vector3	a_b;
	double		ab2;
	double		ap;
	double		t;

	a_b = vec3_sub(B, A); // get the vector from A to B
	ab2 = dot_pd(a_b, a_b); // get the dot product of the vector from A to B
	a_p = vec3_sub(P, A); // get the vector from A to P
	ap = dot_pd(a_p, a_b); // get the dot product of the vector from A to P and the vector from A to B
	t = ap / ab2; // get the ratio of the dot product of the vector from A to P and the vector from A to B to the dot product of the vector from A to B
	if (t < 0) // if the ratio is less than 0, set the ratio to 0
		t = 0;
	else if (t > 1) // if the ratio is greater than 1, set the ratio to 1
		t = 1;
	return (vec3_add(A, vec3_mult(a_b, t))); // return the closest point on the cylinder to the point of impact
}

// get the normal of the cylinder at the point of impact
static void	init_imp(t_impact *imp, double tmp, t_cylinder *cyl, t_ray r)
{
	imp->distance = tmp; // update the distance
	imp->point = vec3_add(r.origin, vec3_mult(r.dir, tmp)); // get the point of impact
	imp->normal = cyl->dir; // get the normal of the cylinder
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
		tmp = cylinder_intersection(r, *cyl, &is_side); // check if the ray hits the cylinder. If it does, update the impact
		if (tmp < imp->distance && tmp > 0) // if the distance is less than the impact distance and greater than 0
		{
			*objs = cyl; // set the object to cylinder
			init_imp(imp, tmp, cyl, r); // initialize the impact
			if (is_side) // if the ray hits the side of the cylinder
				imp->normal = vec3_norm(vec3_sub(imp->point,
							closest_point(cyl->pos, vec3_add(cyl->pos,
									vec3_mult(cyl->dir, cyl->height)),
								imp->point))); // get the normal of the cylinder at the point of impact
			imp->normal = vec3_norm(imp->normal); // normalize the normal
			imp->object = "cy"; // set the object to cylinder
		}
		lst = lst->next;
	}
}
