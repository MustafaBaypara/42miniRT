/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:51:44 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/10 16:52:39 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*set_color(int r, int g, int b)
{
	t_color	*color;

	color = ft_calloc(1, sizeof(t_color));
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}
