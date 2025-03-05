/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:05:06 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/05 17:33:27 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*add_color(t_color color, t_color color2)
{
	t_color	*new_color;

	new_color = int_color(color.r + color2.r,
			color.g + color2.g,
			color.b + color2.b);
	return (new_color);
}

void	min_color(t_color *color)
{
	color->r = get_mini(color->r, 255);
	color->g = get_mini(color->g, 255);
	color->b = get_mini(color->b, 255);
}
