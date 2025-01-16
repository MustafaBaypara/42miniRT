/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:48:23 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/16 18:27:38 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	dot_light_func(t_impact *imp, t_light *light, t_ray to_light)
{
	double	dot_light;

	dot_light = get_maxf(dot_pd(imp->normal, to_light.dir), 0)
		/ (distance(imp->point, light->position)
			* distance(imp->point, light->position));
	return (dot_light);
}

t_color	*lighting(t_scene *sc, t_impact *imp, t_color *color)
{
	t_list		*lights;
	t_light		*light;
	t_ray		to_light;
	void		*obstacle;
	t_impact	*imp_objs;
	t_color		diffuse;
	double		dot_light;
	t_color		color_l;

	diffuse = *int_color(0, 0, 0);
	lights = sc->lights;
	while (lights->next)
	{
		obstacle = NULL;
		light = (t_light *)lights->content;
		to_light = new_ray(imp->point, vec3_sub(light->position, imp->point));
		to_light.origin = vec3_add(to_light.origin, vec3_mult(to_light.dir, EPSILON));
		to_light.dir = vec3_norm(to_light.dir);
		imp_objs = check_objects(to_light, sc, &obstacle);
		if (imp_objs->distance > distance(imp->point, light->position))
		{
			dot_light = dot_light_func(imp, light, to_light);
			color_l = *mult_color_d(light->color, dot_light);
			diffuse = *add_color(diffuse, color_l);
		}
		lights = lights->next;
	}
	diffuse = *mult_color_d(diffuse, ALBEDO);
	*color = *mult_color(*add_color(*sc->al_color, diffuse), *color);
	min_color(color);
	return (NULL);
}
