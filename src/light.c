/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:48:23 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/05 01:32:57 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray	to_light(t_impact *imp, t_light *light)
{
	t_ray	to_light;

	to_light = new_ray(imp->point, vec3_sub(light->position, imp->point));
	to_light.origin = vec3_add(to_light.origin,
			vec3_mult(to_light.dir, EPSILON));
	to_light.dir = vec3_norm(to_light.dir);
	return (to_light);
}

//  max(0, n.l) / 1 / d²
static double	dot_light_func(t_impact *imp, t_light *light, t_ray to_light)
{
	double	dot_light;

	dot_light = get_maxf(dot_pd(imp->normal, to_light.dir), 0)
		/ (distance(imp->point, light->position)
			* distance(imp->point, light->position));
	return (dot_light);
}

static void	light_ext(t_scene *sc, t_color *color, t_color *diffuse)
{
	*diffuse = *mult_color_d(*diffuse, ALBEDO);
	*color = *mult_color(*add_color(*sc->al_color, *diffuse), *color);
	min_color(color);
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
		l->ray_to_light = to_light(imp, light);
		imp_objs = check_objects(l->ray_to_light, sc, &l->obstacle);
		if (imp_objs->distance > distance(imp->point, light->position))
		{
			l->dot_light = dot_light_func(imp, light, l->ray_to_light);
			l->color_l = *mult_color_d(light->color, l->dot_light);
			l->diffuse = *add_color(l->diffuse, l->color_l);
		}
		lights = lights->next;
	}
	light_ext(sc, color, &l->diffuse);
	return (NULL);
}
