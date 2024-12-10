/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:43:04 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/10 17:52:40 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	imaging(t_window *window)
{
	t_size		pixels;
	t_ray		ray;
	int			depth;
	t_color		*color;
	void		*objects;
	t_impact	*impact;

	pixels.height = -1;
	while (++pixels.height < window->scene->res.height)
	{
		pixels.width = -1;
		while (++pixels.width < window->scene->res.width)
		{
			color = set_color(0, 0, 0);
			depth = 1;
			objects = NULL;
			impact = NULL;
			while (--depth)
			{
				// ray = generate_ray(window->scene->res, pixels);
			}
		}
	}
}
