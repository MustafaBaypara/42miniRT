/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:57:48 by abakirca          #+#    #+#             */
/*   Updated: 2025/01/17 01:48:51 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_camera(t_scene *scene, char **data)
{
	t_camera	*camera;

	camera = galloc(sizeof(*camera));
	if (!(camera))
		error_exit("Malloc failed", 1);
	camera->position = str_to_vect(data[1]);
	camera->orientation = (str_to_vect(data[2]));
	camera->fov = ft_atof(data[3]);
	ft_lstadd_front(&(scene->cameras), ft_lstnew(camera));
}

void	set_light(t_scene *scene, char **data)
{
	t_light		*light;
	double		ratio;

	light = galloc(sizeof(*light));
	if (!(light))
		error_exit("Malloc failed", 1);
	light->position = str_to_vect(data[1]);
	ratio = ft_atof(data[2]) * 255;
	light->color = *mult_color_d(str_to_rgb(data[3]), ratio);
	light->ratio = ratio;
	ft_lstadd_front(&(scene->lights), ft_lstnew(light));
}

void	set_sphere(t_scene *scene, char **strs)
{
	t_sphere	*sphere;
	double		radius;

	sphere = galloc(sizeof(*sphere));
	if (!(sphere))
		error_exit("Malloc failed", 1);
	sphere->pos = str_to_vect(strs[1]);
	radius = ft_atof(strs[2]);
	sphere->radius = radius * radius;
	sphere->color = str_to_rgb(strs[3]);
	ft_lstadd_front(&(scene->spheres), ft_lstnew(sphere));
}

void	set_plane(t_scene *scene, char **strs)
{
	t_plane		*plane;

	plane = galloc(sizeof(*plane));
	if (!(plane))
		error_exit("Malloc failed", 1);
	plane->pos = str_to_vect(strs[1]);
	plane->normal = vec3_norm(str_to_vect(strs[2]));
	plane->color = str_to_rgb(strs[3]);
	ft_lstadd_front(&(scene->planes), ft_lstnew(plane));
}

void	set_cylinder(t_scene *scene, char **strs)
{
	t_cylinder	*cy;
	double		radius;

	cy = galloc(sizeof(*cy));
	if (!(cy))
		error_exit("Malloc failed", 1);
	cy->pos = str_to_vect(strs[1]);
	cy->dir = vec3_norm(str_to_vect(strs[2]));
	radius = ft_atof(strs[3]) / 2;
	cy->radius = radius * radius;
	cy->height = ft_atof(strs[4]);
	cy->pos2 = vec3_add(cy->pos, vec3_mult(cy->dir, cy->height));
	cy->color = str_to_rgb(strs[5]);
	ft_lstadd_front(&(scene->cylinders), ft_lstnew(cy));
}
