/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:28:22 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/06 15:35:31 by mbaypara         ###   ########.fr       */
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
			ray.origin.z - sphere.pos.z);
	if (!quadratic_solver(new_vec3(dot_pd(ray.dir, ray.dir),
				2 * dot_pd(ray.dir, vector),
				dot_pd(vector, vector) - sphere.radius), &a, &b))
		return (0);
	if ((a < 0 && b < 0) || (a > impact->distance && b > impact->distance))
		return (0);
	else if (a <= 0.)
		a = b;
	else if (b <= 0.)
		b = a;
	impact->distance = get_minf(a, b);
	vector = vec3_add(ray.origin, vec3_mult(ray.dir, b));
	impact->normal = vec3_norm(vec3_sub(vector, sphere.pos));
	impact->point = vec3_add(vector, vec3_mult(impact->normal, EPSILON));

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
		if (sphere_intersection(ray, *sphere, impact))
		{
			*obj = sphere;
			impact->object = "sp";
		}
		lst = lst->next;
	}
}
