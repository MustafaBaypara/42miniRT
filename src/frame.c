/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:43:04 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/09 18:22:46 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static void	put_pixel(unsigned char *addr, t_size pos, int color, t_size res)
{
	int		offset;

	offset = (pos.height * res.width + pos.width) * 4;
	*(unsigned int *)(addr + offset) = color;
}

t_ray	new_ray(t_vector3 pos, t_vector3 direction)
{
	t_ray	ray;

	ray.origin = pos;
	ray.dir = direction;
	return (ray);
}

// A helper to rotate v_dir by the camera->orientation (pitch, yaw, roll).
t_vector3	rotate_by_orientation(t_vector3 dir, t_vector3 orient)
{
	double pitch = orient.x;
	double yaw   = orient.y;
	double roll  = orient.z;

	double cp = cos(pitch), sp = sin(pitch);
	double cy = cos(yaw),   sy = sin(yaw);
	double cr = cos(roll),  sr = sin(roll);

	// Rotate around X (pitch)
	double ny = dir.y * cp - dir.z * sp;
	double nz = dir.y * sp + dir.z * cp;
	dir.y = ny; dir.z = nz;

	// Rotate around Y (yaw)
	double nx = dir.x * cy + dir.z * sy;
	nz = -dir.x * sy + dir.z * cy;
	dir.x = nx; dir.z = nz;

	// Rotate around Z (roll)
	nx = dir.x * cr - dir.y * sr;
	ny = dir.x * sr + dir.y * cr;
	dir.x = nx; dir.y = ny;

	return (dir);
}

// Modify generate_ray so it applies the camera orientation
t_ray	generate_ray(t_camera *camera, t_size res, int i, int j)
{
	t_vector3	v_dir;
	int			x;

	v_dir.x = j + 0.5 - res.width * 0.5;
	v_dir.y = i + 0.5 - res.height * 0.5;
	x = (res.width > res.height) ? res.width : res.height;
	v_dir.z = x / (2.0 * tan((camera->fov * M_PI * 0.5) / 180.0));
	v_dir.y = -v_dir.y;
	v_dir.z = -v_dir.z;

	v_dir = rotate_by_orientation(v_dir, camera->orientation);

	return (new_ray(camera->position, vec3_norm(v_dir)));
}

t_impact	*check_objects(t_ray ray, t_scene *scene, void **object)
{
	t_impact	*impact;

	impact = ft_calloc(1, sizeof(t_impact));
	impact->object = ft_calloc(3, sizeof(char));
	impact->distance = INFINITY;
	sphere_ray(ray, scene, impact, object);
	cyl_ray(ray, scene, impact, object);
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
	while (++pixels.height < sc->res.height)
	{
		pixels.width = -1;
		while (++pixels.width < sc->res.width)
		{
			color = int_color(0, 0, 0);
			depth = 1;
			objects = NULL;
			imp = NULL;
			while (depth--)
			{
				ray = generate_ray(cam, sc->res, pixels.height, pixels.width);
				imp = check_objects(ray, sc, &objects);
				if (objects)
				{
					*color = object_color(imp->object, objects);
					if (dot_pd(imp->normal, ray.dir) >= 0)
						imp->normal = vec3_minus(imp->normal);
					lighting(sc, imp, color, pixels);
				}
			}
			put_pixel(win->frame->addr, pixels, color_int(*color), sc->res);
			free(color);
		}
	}
}
