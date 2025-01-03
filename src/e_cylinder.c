/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:33:19 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/03 16:57:18 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	cylinder_ray(t_ray ray, t_scene *sc, t_impact *imp, void **objs)
{
	t_list		*lst;
	t_cylinder	*cyl;
	double		tmp;
	int			is_side;

	lst = sc->cylinders;
	while (lst->next)
	{
		is_side = 0;
		cyl = (t_cylinder *)lst->content;
		tmp = cylinder_intersection(ray, *cyl, imp, &is_side);
		if (tmp < imp->distance && tmp > 0)
		{
			*objs = cyl;
			imp->distance = tmp;
			imp->point = new_vec3(tmp * ray.direction.x, tmp * ray.direction.y,
					tmp * ray.direction.z);
			if (is_side)
				imp->normal = new_vec3()
	}
}
