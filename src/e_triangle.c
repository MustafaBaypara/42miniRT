/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_triangle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 01:43:47 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/03 18:44:09 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_triangle(t_scene *scene, char **strs)
{
	t_triangle	*tr;
	t_list		*new;

	tr = ft_malloc(sizeof(*tr));
	tr->v0 = str_to_vect(strs[1]);
	tr->v1 = str_to_vect(strs[2]);
	tr->v2 = str_to_vect(strs[3]);
	tr->color = str_to_rgb(strs[4]);
	new = ft_lstnew(tr);
	if (!new)
		error_exit("Malloc failed", 1);
	ft_lstadd_front(&(scene->triangles), new);
}

static t_vector3	cross_pd(t_vector3 v1, t_vector3 v2)
{
	t_vector3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

static int	tri_isec(t_ray ray, t_triangle tri, t_impact *imp)
{
	tri.edge1 = vec3_sub(tri.v1, tri.v0);
	tri.edge2 = vec3_sub(tri.v2, tri.v0);
	tri.h = cross_pd(ray.dir, tri.edge2);
	tri.utls.x = dot_pd(tri.edge1, tri.h);
	if (fabs(tri.utls.x) < EPSILON)
		return (0);
	tri.utls.x = 1.0 / tri.utls.x;
	tri.s = vec3_sub(ray.origin, tri.v0);
	tri.utls.y = tri.utls.x * dot_pd(tri.s, tri.h);
	if (tri.utls.y < 0.0 || tri.utls.y > 1.0)
		return (0);
	tri.q = cross_pd(tri.s, tri.edge1);
	tri.utls.z = tri.utls.x * dot_pd(ray.dir, tri.q);
	if (tri.utls.z < 0.0 || tri.utls.y + tri.utls.z > 1.0)
		return (0);
	tri.utls.z = tri.utls.x * dot_pd(tri.edge2, tri.q);
	if (tri.utls.z > EPSILON && tri.utls.z < imp->distance)
	{
		imp->distance = tri.utls.z;
		imp->point = vec3_add(ray.origin, vec3_mult(ray.dir, tri.utls.z));
		imp->normal = vec3_norm(cross_pd(tri.edge1, tri.edge2));
		return (1);
	}
	return (0);
}

void	triangle_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj)
{
	t_list		*lst;
	t_triangle	*triangle;

	lst = scene->triangles;
	while (lst->next)
	{
		triangle = (t_triangle *)(lst->content);
		if (tri_isec(ray, *triangle, impact))
		{
			*obj = triangle;
			impact->object = "tr";
		}
		lst = lst->next;
	}
}
