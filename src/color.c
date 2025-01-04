/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:49:41 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/04 17:38:41 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	object_color(char *type, void *obj)
{
	if (!ft_strcmp(type, "sp"))
		return (((t_sphere *)obj)->color);
	if (!ft_strcmp(type, "pl"))
		return (((t_plane *)obj)->color);
	if (!ft_strcmp(type, "cy"))
		return (((t_cylinder *)obj)->color);
}

int	color_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

t_color	*int_color(int r, int g, int b)
{
	t_color	*color;

	color = ft_calloc(1, sizeof(t_color));
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

t_color	*mult_color(t_color color, t_color color2)
{
	t_color	*new_color;

	new_color = int_color(color.r * (color2.r / 255),
			color.g * (color2.g / 255),
			color.b * (color2.b / 255));
	return (new_color);
}

t_color	*mult_color_d(t_color color, double d)
{
	t_color	*new_color;

	new_color = int_color(color.r * d,
			color.g * d,
			color.b * d);
	return (new_color);
}
