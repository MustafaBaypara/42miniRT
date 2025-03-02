/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_triangle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 01:43:47 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/02 18:19:40 by abakirca         ###   ########.fr       */
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

// this code uses an algorithm called Moller-Trumbore algorithm to check if the ray hits the triangle
static int	tri_isec(t_ray ray, t_triangle tri, t_impact *imp)
{
	// We select a base which is v0 here and calculate the two edges of the triangle
	tri.edge1 = vec3_sub(tri.v1, tri.v0);
	tri.edge2 = vec3_sub(tri.v2, tri.v0);
	// we use a helper variable to store the cross product of the edge2 and ray.dir. This is used to calculate the determinant
	tri.h = cross_pd(ray.dir, tri.edge2);
	// we calculate the dot product of the edge1 and the helper variable which gives us the determinant that means the ray is parallel to the triangle or not
	tri.utls.x = dot_pd(tri.edge1, tri.h);
	// if the determinant is close to 0, the ray is parallel to the triangle
	if (fabs(tri.utls.x) < EPSILON)
		return (0);
	// this is just 1/determinant which is used to calculate the barycentric coordinates.
	// We do this so that we don't have to calculate the determinant again and again.
	// Also Multiplying by 1/determinant is faster than dividing by determinant
	// Which is important for real-time rendering
	tri.utls.x = 1.0 / tri.utls.x;
	// Now that we know the ray is not parallel to the triangle, we calculate the barycentric coordinates
	// tri.s is the vector from the origin of the ray to the vertex of the triangle
	// this calculation tells us how far and what direction we have to move from the origin of the ray to reach the vertex of the triangle
	tri.s = vec3_sub(ray.origin, tri.v0);
	// we calculate the dot product of the s and the helper variable which gives us the barycentric coordinate u
	// which tells us where the ray's intersection point is relative to v0 and other edges of the triangle
	tri.utls.y = tri.utls.x * dot_pd(tri.s, tri.h);
	// if u < 0, the ray is outside the triangle, beyond v0 in the opposite direction of the v1
	// if u > 1, the ray is outside the triangle, beyond v1 in the direction of the v2
	// if u is between 0 and 1, the ray hit is within the triangle
	if (tri.utls.y < 0.0 || tri.utls.y > 1.0)
		return (0);
	// below we calculate the barycentric coordinate v
	// which tells us where the ray's intersection point is relative to v0 and other edges of the triangle
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
		triangle = (t_triangle *)(lst->content); // get the triangle from the list
		if (tri_isec(ray, *triangle, impact)) // check if the ray hits the triangle. If it does, update the impact
		{
			*obj = triangle; // set the object to the triangle
			impact->object = "tr"; // set the object to triangle
		}
		lst = lst->next;
	}
}
