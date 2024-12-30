/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:48:23 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/30 17:11:34 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	*calc_d(t_light *light, t_impact *imp, t_scene *sc, double d_l)
{
	t_ray		to_light;
	void		*obstacle;
	t_impact	*imp_objs;
	t_color		diffuse;
	t_color		color_l;

	diffuse = *int_color(0, 0, 0);
	obstacle = NULL;
	to_light = new_ray(imp->point, vec3_sub(light->position, imp->point));
	imp_objs = check_objects(to_light, sc, &obstacle);

	if (imp_objs->distance > distance(imp->point, light->position))
	{
		d_l = get_maxf(dot_pd(imp->normal, to_light.direction), 0)
			/ (distance(imp->point, light->position)
				* distance(imp->point, light->position));
		color_l = *mult_color_d(light->color, d_l);
		diffuse = *add_color(diffuse, color_l);
	}

	return (int_color(diffuse.r, diffuse.g, diffuse.b));
}

t_color	process_lights(t_scene *sc, t_impact *imp)
{
	t_list	*lights;
	t_color	total_diffuse;
	t_light	*light;
	t_color	*diffuse;

	total_diffuse = *int_color(0, 0, 0);
	lights = sc->lights;
	while (lights->next)
	{
		light = (t_light *)lights->content;
		diffuse = calc_d(light, imp, sc, 0);
		total_diffuse = *add_color(total_diffuse, *diffuse);
		free(diffuse);
		lights = lights->next;
	}

	return (*mult_color_d(total_diffuse, ALBEDO));
}

t_color	*lighting(t_scene *sc, t_impact *imp, t_color *color, t_size pixel)
{
	t_color	diffuse;

	diffuse = process_lights(sc, imp);
	*color = *mult_color(*add_color(sc->al_color, diffuse), *color);
	min_color(color);

	return (NULL);
}

