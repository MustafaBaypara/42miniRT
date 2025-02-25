/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:05:06 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 20:57:32 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// add_color adds two colors
t_color	*add_color(t_color color, t_color color2)
{
	t_color	*new_color;

	new_color = int_color(color.r + color2.r,
			color.g + color2.g,
			color.b + color2.b); // add the values of the colors in order to get the new color
	return (new_color);
}

// min_color makes sure that the color is within the range of 0 and 255
void	min_color(t_color *color)
{
	color->r = get_mini(color->r, 255);
	color->g = get_mini(color->g, 255);
	color->b = get_mini(color->b, 255);
}
