/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:56:49 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/05 17:34:02 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_vector3 pos, t_vector3 dir)
{
	t_ray	ray;

	ray.origin = pos;
	ray.dir = dir;
	return (ray);
}

static void	init_vectors(t_vector3 *p, t_vector3 *y, t_vector3 *r, t_vector3 o)
{
	r->x = cos(o.z * M_PI);
	r->y = sin(o.z * M_PI);
	r->z = 0;
	y->x = cos(o.y * M_PI);
	y->y = sin(o.y * M_PI);
	y->z = 0;
	p->x = cos(o.x * M_PI);
	p->y = sin(o.x * M_PI);
}

static t_vector3	rotate_by_orientation(t_vector3 dir, t_vector3 orient)
{
	t_vector3	pitch;
	t_vector3	yaw;
	t_vector3	roll;
	t_vector3	temp;

	init_vectors(&pitch, &yaw, &roll, orient);
	temp.x = dir.x * roll.x - dir.y * roll.y;
	temp.y = dir.x * roll.y + dir.y * roll.x;
	dir.x = temp.x;
	dir.y = temp.y;
	temp.y = dir.y * pitch.x - dir.z * pitch.y;
	temp.z = dir.y * pitch.y + dir.z * pitch.x;
	dir.y = temp.y;
	dir.z = temp.z;
	temp.x = dir.x * yaw.x + dir.z * yaw.y;
	temp.z = -dir.x * yaw.y + dir.z * yaw.x;
	dir.x = temp.x;
	dir.z = temp.z;
	return (dir);
}

t_ray	generate_ray(t_camera *camera, t_size res, int i, int j)
{
	t_vector3	v_dir;
	int			x;

	v_dir.x = j + 0.5 - res.width * 0.5;
	v_dir.y = i + 0.5 - res.height * 0.5;
	if (res.width > res.height)
		x = res.width;
	else
		x = res.height;
	v_dir.z = x / (2.0 * tan((camera->fov * M_PI * 0.5) / 180.0));
	v_dir.y = -v_dir.y;
	v_dir.z = -v_dir.z;
	v_dir = rotate_by_orientation(v_dir, camera->orientation);
	return (new_ray(camera->position, vec3_norm(v_dir)));
}
