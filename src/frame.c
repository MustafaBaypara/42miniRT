/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:43:04 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/03 16:42:33 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static void	put_pixel(char *addr, t_size pos, int color, t_size res)
{
	int		offset;

	offset = (pos.height * res.width + pos.width) * 4;
	*(unsigned int *)(addr + offset) = color;
}

t_impact	*check_objects(t_ray ray, t_scene *scene, void **object)
{
	t_impact	*impact;

	impact = ft_calloc(1, sizeof(t_impact));
	if (!impact)
		error_exit("Malloc failed", 1);
	impact->object = ft_calloc(3, sizeof(char));
	if (!impact->object)
		error_exit("Malloc failed", 1);
	impact->distance = INFINITY;
	sphere_ray(ray, scene, impact, object);
	plane_ray(ray, scene, impact, object);
	cyl_ray(ray, scene, impact, object);
	triangle_ray(ray, scene, impact, object);
	return (impact);
}

static void	init_clr_obj(t_color **color, void **objects)
{
	*color = int_color(0, 0, 0);
	*objects = NULL;
}

static void	do_somethings(t_scene *sc, t_color *color, t_size px, t_window *win)
{
	put_pixel(win->frame->addr, px, color_int(*color), sc->res);
	gfree(color);
	printf("Loading frame: %d%%\r", (int)((px.height * sc->res.width + px.width)
			* 100 / (sc->res.width * sc->res.height)));
}

void	imaging(t_window *win, t_camera *cam, t_scene *sc, t_impact *imp)
{
	t_size		pixels;
	t_ray		ray;
	t_color		*color;
	void		*objects;

	pixels.height = -1;
	while (++pixels.height < sc->res.height)
	{
		pixels.width = -1;
		while (++pixels.width < sc->res.width)
		{
			init_clr_obj(&color, &objects);
			ray = generate_ray(cam, sc->res, pixels.height, pixels.width);
			imp = check_objects(ray, sc, &objects);
			if (objects)
			{
				*color = object_color(imp->object, objects);
				if (dot_pd(imp->normal, ray.dir) >= 0)
					imp->normal = vec3_minus(imp->normal);
				lighting(sc, imp, color);
			}
			do_somethings(sc, color, pixels, win);
		}
	}
	printf("\033[KScene Loaded Successfully!\n");
}
