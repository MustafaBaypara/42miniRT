/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:49:41 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/26 13:52:02 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	object_color(char *type, void *obj)
{
	if (!ft_strcmp(type, "sphere"))
		return (((t_sphere *)obj)->color);
}