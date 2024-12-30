/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:05:06 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/30 13:14:47 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*add_color(t_color color, t_color color2)
{
	t_color	*new_color;

	new_color = int_color(color.r + color.r,
			color.g + color.g,
			color.b + color.b);
	return (new_color);
}

void	min_color(t_color *color)
{
	color->r = get_minf(color->r, 255);
	color->g = get_minf(color->g, 255);
	color->b = get_minf(color->b, 255);
}
