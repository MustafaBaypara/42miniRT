/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_triangle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 01:43:47 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 20:52:14 by abakirca         ###   ########.fr       */
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

// cross_pd calculates the cross product of two vectors
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
	tri.edge1 = vec3_sub(tri.v1, tri.v0); // get the edge of the triangle
	tri.edge2 = vec3_sub(tri.v2, tri.v0); // get the edge of the triangle
	tri.h = cross_pd(ray.dir, tri.edge2); // get the cross product of the direction of the ray and the edge of the triangle
	tri.utls.x = dot_pd(tri.edge1, tri.h); // get the dot product of the edge of the triangle and the cross product of the direction of the ray and the edge of the triangle
	if (fabs(tri.utls.x) < EPSILON) // if the absolute value of the dot product is less than EPSILON, return 0
		return (0);
	tri.utls.x = 1.0 / tri.utls.x; // get the reciprocal of the dot product
	tri.s = vec3_sub(ray.origin, tri.v0); // get the vector from the origin of the ray to the vertex of the triangle
	tri.utls.y = tri.utls.x * dot_pd(tri.s, tri.h); // get the dot product of the vector from the origin of the ray to the vertex of the triangle and the cross product of the direction of the ray and the edge of the triangle
	if (tri.utls.y < 0.0 || tri.utls.y > 1.0) // if the dot product is less than 0 or greater than 1, return 0
		return (0);
	tri.q = cross_pd(tri.s, tri.edge1); // get the cross product of the vector from the origin of the ray to the vertex of the triangle and the edge of the triangle
	tri.utls.z = tri.utls.x * dot_pd(ray.dir, tri.q); // get the dot product of the direction of the ray and the cross product of the vector from the origin of the ray to the vertex of the triangle and the edge of the triangle
	if (tri.utls.z < 0.0 || tri.utls.y + tri.utls.z > 1.0) // if the dot product is less than 0 or the sum of the dot product and the dot product of the vector from the origin of the ray to the vertex of the triangle and the edge of the triangle is greater than 1,
		return (0);
	tri.utls.z = tri.utls.x * dot_pd(tri.edge2, tri.q); // get the dot product of the edge of the triangle and the cross product of the vector from the origin of the ray to the vertex of the triangle and the edge of the triangle
	if (tri.utls.z > EPSILON && tri.utls.z < imp->distance) // if the dot product is greater than EPSILON and less than the distance of the impact, update the impact
	{
		imp->distance = tri.utls.z; // update the distance
		imp->point = vec3_add(ray.origin, vec3_mult(ray.dir, tri.utls.z)); // get the point of impact
		imp->normal = vec3_norm(cross_pd(tri.edge1, tri.edge2)); // get the normal of the triangle at the point of impact
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
		triangle = (t_triangle *)(lst->content); // get the triangle from the list
		if (tri_isec(ray, *triangle, impact)) // check if the ray hits the triangle. If it does, update the impact
		{
			*obj = triangle; // set the object to the triangle
			impact->object = "tr"; // set the object to triangle
		}
		lst = lst->next;
	}
}
