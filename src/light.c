/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:48:23 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/30 17:12:56 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*lighting(t_scene *sc, t_impact *imp, t_color *color, t_size pixel)
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
		imp_objs = check_objects(to_light, sc, &obstacle);
		if (imp_objs->distance > distance(imp->point, light->position))
		{
			dot_light = get_maxf(dot_pd(imp->normal, to_light.direction), 0.0)
				/ (distance(imp->point, light->position)
					* distance(imp->point, light->position));
			color_l = *mult_color_d(light->color, dot_light);
			diffuse = *add_color(diffuse, color_l);
		}
		lights = lights->next;
	}
	diffuse = *mult_color_d(diffuse, ALBEDO);
	*color = *mult_color(*add_color(sc->al_color, diffuse), *color);
	min_color(color);
	return (NULL);
}
