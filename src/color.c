/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:49:41 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 21:09:43 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// object_color gets the color of the object
t_color	object_color(char *type, void *obj)
{
	if (!ft_strcmp(type, "sp"))
		return (((t_sphere *)obj)->color);
	if (!ft_strcmp(type, "pl"))
		return (((t_plane *)obj)->color);
	if (!ft_strcmp(type, "cy"))
		return (((t_cylinder *)obj)->color);
	if (!ft_strcmp(type, "tr"))
		return (((t_triangle *)obj)->color);
	return ((t_color){0, 0, 0});
}

// color_int converts a color to an integer which is used to put the pixel on the screen
int	color_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

// int_color creates a new color with the given r, g, and b values
t_color	*int_color(int r, int g, int b)
{
	t_color	*color;

	color = ft_gcalloc(1, sizeof(t_color));
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

//mult_color multiplies two colors which is used for the color of the object and the color of the light
t_color	*mult_color(t_color color, t_color color2)
{
	t_color	*new_color;

	new_color = int_color(color.r * (color2.r / 255.),
			color.g * (color2.g / 255.),
			color.b * (color2.b / 255.));
	return (new_color);
}

// mult_color_d multiplies a color by a double which is used for the intensity of the light
t_color	*mult_color_d(t_color color, double d)
{
	t_color	*new_color;

	new_color = int_color(color.r * d,
			color.g * d,
			color.b * d);
	return (new_color);
}
