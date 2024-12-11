/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_plane_sphere.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:28:22 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/11 18:02:06 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sphere_intersection(t_ray ray, t_sphere sphere, t_impact *impact)
{
	t_vector3	vector;
	double		a;
	double		b;

	vector = new_vec3(ray.origin.x - sphere.position.x,
			ray.origin.y - sphere.position.y,
			ray.origin.z - sphere.position.z);
	if (!quadratic_solver(new_vec3(dot_product(ray.direction, ray.direction),
				2 * dot_product(ray.direction, vector),
				dot_product(vector, vector) - sphere.radius * sphere.radius),
			&a, &b))
		return (0);

}

void	sphere_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj)
{
	t_list		*lst;
	t_sphere	*sphere;

	lst = scene->spheres;
	while (lst->next)
	{
		sphere = (t_sphere *)lst->content;
		if (sphere_intersection(ray, *sphere, impact))
			*obj = sphere;
	}
}
