/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:58:48 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/05 14:47:12 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_size
{
	int	width;
	int	height;
}	t_size;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	direction;
}	t_ray;

typedef struct s_impact
{
	char		*object;
	double		distance;
	t_vector3	point;
	t_vector3	normal;
}	t_impact;

#endif