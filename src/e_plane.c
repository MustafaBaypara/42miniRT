/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:18:30 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/04 01:26:26 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static int	plane_intersection(t_ray ray, t_plane plane, t_impact *impact)
{
	double	denom;
	double	t;

	denom = dot_pd(plane.normal, ray.dir); // 0 ise isin ve duzlem paralel (cok nadir)
	if (fabs(denom) > EPSILON) // mutlak degeri epsilon dan buyukse ise paralel degil (ise yarar)
	{
		t = dot_pd(vec3_sub(plane.pos, ray.origin), plane.normal) / denom;
		// kesisim mesafesi hesaplaniyor. isinin duzleme mesafesi // denom aciyi hesaba katmasi icin
		
		// kesisim kameranin onundemi ve kameraya en yakin kesisim alinir
		if (t > EPSILON && t < impact->distance)
		{
			// kesisim noktasi uygunsa impacta atanir
			impact->distance = t;
			if (denom < 0) // isin duzlemin on yuzune carparsa
				impact->normal = vec3_norm(plane.normal);
			else // isin duzlemin arka yuzune carparsa
				impact->normal = vec3_norm(vec3_mult(plane.normal, -1));
			
			// kesisim noktasi hesaplanir ve epsilon ile kaydirilir
			impact->point = vec3_add(ray.origin, vec3_mult(ray.dir, t));

			// kesisim noktasi normali ile epsilon ile kaydirilir
			impact->point = vec3_add(impact->point,
					vec3_mult(impact->normal, EPSILON));
			return (1);
		}
	}
	return (0);
}

void	plane_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj)
{
	t_list	*lst;
	t_plane	*plane;

	lst = scene->planes;
	while (lst->next)
	{
		plane = (t_plane *)lst->content;
		if (plane_intersection(ray, *plane, impact))
		{
			*obj = plane;
			impact->object = "pl";
		}
		lst = lst->next;
	}
}
