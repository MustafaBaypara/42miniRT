/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:57:48 by abakirca          #+#    #+#             */
/*   Updated: 2025/03/03 20:09:56 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_camera(t_scene *scene, char **data)
{
	t_camera	*camera;
	t_list		*new;

	camera = ft_malloc(sizeof(*camera));
	camera->position = str_to_vect(data[1]);
	camera->orientation = (str_to_vect(data[2]));
	camera->fov = ft_atof(data[3]);
	new = ft_lstnew(camera);
	if (!new)
		error_exit("Malloc failed", 1);
	ft_lstadd_front(&(scene->cameras), new);
}

void	set_light(t_scene *scene, char **data)
{
	t_light		*light;
	double		ratio;
	t_list		*new;

	light = ft_malloc(sizeof(*light));
	light->position = str_to_vect(data[1]);
	ratio = ft_atof(data[2]) * 255;
	light->color = *mult_color_d(str_to_rgb(data[3]), ratio);
	light->ratio = ratio;
	new = ft_lstnew(light);
	if (!new)
		error_exit("Malloc failed", 1);
	ft_lstadd_front(&(scene->lights), new);
}

void	set_sphere(t_scene *scene, char **strs)
{
	t_sphere	*sphere;
	double		radius;
	t_list		*new;

	sphere = ft_malloc(sizeof(*sphere));
	sphere->pos = str_to_vect(strs[1]);
	radius = ft_atof(strs[2]);
	sphere->radius = radius * radius;
	sphere->color = str_to_rgb(strs[3]);
	new = ft_lstnew(sphere);
	if (!new)
		error_exit("Malloc failed", 1);
	ft_lstadd_front(&(scene->spheres), new);
}

void	set_plane(t_scene *scene, char **strs)
{
	t_plane		*plane;
	t_list		*new;

	plane = ft_malloc(sizeof(*plane));
	plane->pos = str_to_vect(strs[1]);
	plane->normal = vec3_norm(str_to_vect(strs[2]));
	plane->color = str_to_rgb(strs[3]);
	new = ft_lstnew(plane);
	if (!new)
		error_exit("Malloc failed", 1);
	ft_lstadd_front(&(scene->planes), new);
}

void	set_cylinder(t_scene *scene, char **strs)
{
	t_cylinder	*cy;
	double		radius;
	t_list		*new;

	cy = ft_malloc(sizeof(*cy));
	cy->pos = str_to_vect(strs[1]);
	cy->dir = vec3_norm(str_to_vect(strs[2]));
	radius = ft_atof(strs[3]) / 2;
	cy->radius = radius * radius;
	cy->height = ft_atof(strs[4]);
	cy->pos2 = vec3_add(cy->pos, vec3_mult(cy->dir, cy->height));
	cy->color = str_to_rgb(strs[5]);
	new = ft_lstnew(cy);
	if (!new)
		error_exit("Malloc failed", 1);
	ft_lstadd_front(&(scene->cylinders), new);
}
