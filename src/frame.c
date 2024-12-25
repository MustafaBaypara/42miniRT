/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:43:04 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/25 14:35:47 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_ray	new_ray(t_vector3 pos, t_vector3 direction)
{
	t_ray	ray;

	ray.origin = pos;
	ray.direction = direction;
	return (ray);
}

t_ray	generate_ray(t_camera *camera, t_size res, int i, int j)
{
	t_vector3	v_dir;
	int			x;

	v_dir.x = j + 0.5 - res.width / 2;
	v_dir.y = i + 0.5 - res.height / 2;

	if (res.width > res.height)
		x = res.width;
	else
		x = res.height;

	v_dir.z = x / (2 * tan(camera->fov * M_PI * 0.5 / 180.0));

	return (new_ray(camera->position, vec3_norm(v_dir)));
}

t_impact	*check_objects(t_ray ray, t_scene *scene, void **object)
{
	t_impact	*impact;

	impact = ft_calloc(1, sizeof(t_impact));
	impact->object = ft_calloc(3, sizeof(char));
	impact->distance = INFINITY;
	sphere_ray(ray, scene, impact, object);
	plane_ray(ray, scene, impact, object);
	//cylinder_ray(ray, scene, impact, object);
	return (impact);
}

void	imaging(t_window *win, t_camera *cam, t_scene *sc, t_impact *imp)
{
	t_size		pixels;
	t_ray		ray;
	int			depth;
	t_color		*color;
	void		*objects;

	pixels.height = -1;
	while (++pixels.height < win->scene->res.height)
	{
		pixels.width = -1;
		while (++pixels.width < win->scene->res.width)
		{
			color = set_color(0, 0, 0);
			depth = 1;
			objects = NULL;
			imp = NULL;
			while (--depth)
			{
				ray = generate_ray(cam, sc->res, pixels.height, pixels.width);
			}
		}
	}
}
