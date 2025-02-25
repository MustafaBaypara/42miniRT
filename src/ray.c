/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:56:49 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 21:07:21 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// create a new ray with the given position and direction
t_ray	new_ray(t_vector3 pos, t_vector3 dir)
{
	t_ray	ray;

	ray.origin = pos;
	ray.dir = dir;
	return (ray);
}

// initialize the pitch, yaw and roll vectors
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

// ray direction is rotated by the orientation of the camera
static t_vector3	rotate_by_orientation(t_vector3 dir, t_vector3 orient)
{
	t_vector3	pitch;
	t_vector3	yaw;
	t_vector3	roll;
	t_vector3	temp;

	init_vectors(&pitch, &yaw, &roll, orient); // initialize the pitch, yaw and roll vectors which are used to rotate the direction of the ray
	temp.x = dir.x * roll.x - dir.y * roll.y; // rotate the direction of the ray by the orientation of the camera
	temp.y = dir.x * roll.y + dir.y * roll.x; // rotate the direction of the ray by the orientation of the camera
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
	t_vector3	v_dir; // vector direction
	int			x; // width or height

	v_dir.x = j + 0.5 - res.width * 0.5; // set the x value of the vector direction
	v_dir.y = i + 0.5 - res.height * 0.5; // set the y value of the vector direction
	if (res.width > res.height) // if the width is greater than the height
		x = res.width; // set x to the width
	else
		x = res.height; // otherwise set x to the height
	v_dir.z = x / (2.0 * tan((camera->fov * M_PI * 0.5) / 180.0)); // set the z value of the vector direction. this is the distance from the camera to the screen a.k.a field of view
	v_dir.y = -v_dir.y; // set the y value of the vector direction to the negative of itself
	v_dir.z = -v_dir.z; // set the z value of the vector direction to the negative of itself
	v_dir = rotate_by_orientation(v_dir, camera->orientation); // rotate the vector direction by the orientation of the camera. this is to make sure the camera is looking in the right direction
	return (new_ray(camera->position, vec3_norm(v_dir))); // return a new ray with the position of the camera and the normalized vector direction
}
