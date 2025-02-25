/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:48:23 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 20:57:15 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray	to_light(t_impact *imp, t_light *light)
{
	t_ray	to_light;

	to_light = new_ray(imp->point, vec3_sub(light->position, imp->point)); // get the ray from the point of impact to the position of the light
	to_light.origin = vec3_add(to_light.origin,
			vec3_mult(to_light.dir, EPSILON)); // add EPSILON to the origin of the ray
	to_light.dir = vec3_norm(to_light.dir); // normalize the direction of the ray
	return (to_light);
}

// dot_light_func calculates the dot product of the normal of the impact and the direction of the ray to the light
static double	dot_light_func(t_impact *imp, t_light *light, t_ray to_light)
{
	double	dot_light;

	dot_light = get_maxf(dot_pd(imp->normal, to_light.dir), 0)
		/ (distance(imp->point, light->position)
			* distance(imp->point, light->position)); // get the dot product of the normal of the impact and the direction of the ray to the light
	return (dot_light);
}

// do_somethings does some calculations which are used to calculate the color of the pixel
static void	do_somethings(t_scene *sc, t_color *color, t_color *diffuse)
{
	*diffuse = *mult_color_d(*diffuse, ALBEDO); // multiply the diffuse color by the albedo
	*color = *mult_color(*add_color(*sc->al_color, *diffuse), *color); // add the diffuse color to the ambient light color and multiply it by the color of the object
	min_color(color); // make sure that the color is within the range of 0 and 255
}

t_color	*lighting(t_scene *sc, t_impact *imp, t_color *color)
{
	t_list		*lights;
	t_light		*light;
	t_impact	*imp_objs;
	t_lighting	*l;

	l = (t_lighting *)ft_malloc(sizeof(t_lighting));
	l->diffuse = *int_color(0, 0, 0);
	lights = sc->lights;
	while (lights->next)
	{
		l->obstacle = NULL;
		light = (t_light *)lights->content;
		l->ray_to_light = to_light(imp, light); // get the ray to the light
		imp_objs = check_objects(l->ray_to_light, sc, &l->obstacle);
		if (imp_objs->distance > distance(imp->point, light->position)) // if the distance of the impact is greater than the distance between the point of impact and the position of the light, calculate the diffuse color
		{
			l->dot_light = dot_light_func(imp, light, l->ray_to_light); // get the dot product of the normal of the impact and the direction of the ray to the light
			l->color_l = *mult_color_d(light->color, l->dot_light); // multiply the color of the light by the dot product
			l->diffuse = *add_color(l->diffuse, l->color_l); // add the color to the diffuse color
		}
		lights = lights->next;
	}
	do_somethings(sc, color, &l->diffuse);
	return (NULL);
}
