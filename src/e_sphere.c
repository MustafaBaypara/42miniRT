/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:28:22 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 22:18:20 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	sphere_intersection(t_ray ray, t_sphere sphere, t_impact *impact)
{
	t_vector3	vector;
	double		a;
	double		b;

	vector = new_vec3(ray.origin.x - sphere.pos.x,
			ray.origin.y - sphere.pos.y,
			ray.origin.z - sphere.pos.z); // vector from the origin of the ray to the center of the sphere
	if (!quadratic_solver(new_vec3(dot_pd(ray.dir, ray.dir),
				2 * dot_pd(ray.dir, vector),
				dot_pd(vector, vector) - sphere.radius), &a, &b)) // solve the quadratic equation. quadratic equation means that the equation has a degree of 2. The equation is in the form of ax^2 + bx + c = 0
		return (0);
	if ((a < 0 && b < 0) || (a > impact->distance && b > impact->distance)) // if both a and b are negative or both a and b are greater than the distance, return 0
		return (0);
	else if (a <= 0.) // if a is negative, set a to b
		a = b;
	else if (b <= 0.) // if b is negative, set b to a
		b = a;
	impact->distance = get_minf(a, b); // get the minimum value between a and b
	vector = vec3_add(ray.origin, vec3_mult(ray.dir, b)); // get the vector from the origin of the ray to the point of impact
	impact->normal = vec3_norm(vec3_sub(vector, sphere.pos)); // get the normal of the sphere at the point of impact
	impact->point = vec3_add(vector, vec3_mult(impact->normal, EPSILON)); // get the point of impact
	return (1);
}

void	sphere_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj)
{
	t_list		*lst;
	t_sphere	*sphere;

	lst = scene->spheres;
	while (lst->next)
	{
		sphere = (t_sphere *)(lst->content);
		if (sphere_intersection(ray, *sphere, impact)) // check if the ray hits the sphere. If it does, update the impact
		{
			*obj = sphere;
			impact->object = "sp"; // set the object to sphere
		}
		lst = lst->next;
	}
}
