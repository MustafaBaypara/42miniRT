/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:43:04 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 21:10:44 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

// put_pixel puts the pixel on the screen
static void	put_pixel(char *addr, t_size pos, int color, t_size res)
{
	int		offset;

	offset = (pos.height * res.width + pos.width) * 4; // calculate the offset
	*(unsigned int *)(addr + offset) = color; // put the pixel on the screen
}

t_impact	*check_objects(t_ray ray, t_scene *scene, void **object)
{
	t_impact	*impact; // initialize the impact

	impact = ft_gcalloc(1, sizeof(t_impact));
	impact->object = ft_gcalloc(3, sizeof(char));
	impact->distance = INFINITY; // initialize the distance to infinity. This is to check if the ray hits any object. If it does, the distance will be updated
	sphere_ray(ray, scene, impact, object); // check if the ray hits the sphere
	plane_ray(ray, scene, impact, object); // check if the ray hits the plane
	cyl_ray(ray, scene, impact, object); // check if the ray hits the cylinder
	triangle_ray(ray, scene, impact, object); // check if the ray hits the triangle
	return (impact); // return the impact
}

// initialize the color and objects
static void	init_clr_obj(t_color **color, void **objects)
{
	*color = int_color(0, 0, 0); // initialize the color to black
	*objects = NULL; // initialize the objects to NULL
}

// do_somethings does some calculations which are used to calculate the color of the pixel
static void	do_somethings(t_scene *sc, t_color *color, t_size px, t_window *win)
{
	put_pixel(win->frame->addr, px, color_int(*color), sc->res); // put the pixel on the screen
	gfree(color);
	printf("Loading frame: %d%%\r", (int)((px.height * sc->res.width + px.width)
			* 100 / (sc->res.width * sc->res.height))); // print the percentage of the frame loaded
}

void	imaging(t_window *win, t_camera *cam, t_scene *sc, t_impact *imp)
{
	t_size		pixels;
	t_ray		ray;
	t_color		*color;
	void		*objects;

	pixels.height = -1;
	while (++pixels.height < sc->res.height) // while loop to iterate through the pixels until the height of the screen
	{
		pixels.width = -1;
		while (++pixels.width < sc->res.width) // while loop to iterate through the pixels until the width of the screen
		{
			init_clr_obj(&color, &objects); // initialize the color and objects
			ray = generate_ray(cam, sc->res, pixels.height, pixels.width); // generate the ray
			imp = check_objects(ray, sc, &objects); // check the objects
			if (objects) // if the objects are not NULL
			{
				*color = object_color(imp->object, objects); // get the color of the object
				if (dot_pd(imp->normal, ray.dir) >= 0) // if the dot product of the normal and the direction of the ray is greater than or equal to 0
					imp->normal = vec3_minus(imp->normal); // set the normal to the negative of the normal
				lighting(sc, imp, color); // apply the lighting
			}
			do_somethings(sc, color, pixels, win);
		}
	}
	printf("\033[KScene Loaded Successfully!\n");
}
