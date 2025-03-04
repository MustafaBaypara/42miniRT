/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:54:43 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/04 23:54:15 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../mlx/mlx.h"
#include <math.h>

static void	func_swap(void *a, void *b)
{
	void	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

// ax² + bx + c = 0 point = {a, b, c}
// b² - 4ac = 0 // discriminant
// x = -b ± √(b² - 4ac) / 2a
int	quadratic_solver(t_vector3 point, double *a, double *b)
{
	double	discriminant;
	double	q;

	discriminant = point.y * point.y - 4 * point.x * point.z;
	if (discriminant < 0)
		return (0);
	else if (discriminant == 0)
	{
		*a = -0.5 * point.y / point.x;
		*b = -0.5 * point.y / point.x;
	}
	else
	{
		if (point.y > 0)
			q = -0.5 * (point.y + sqrt(discriminant));
		else
			q = -0.5 * (point.y - sqrt(discriminant));
		*a = q / point.x;
		*b = point.z / q;
	}
	if (*a > *b)
		func_swap(a, b);
	return (1);
}

void	error_exit(char *message, int error_code)
{
	t_window	*win;

	win = getwindow();
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (win->mlx)
	{
		if (win->win)
		{
			mlx_destroy_window(win->mlx, win->win);
			if (win->frame->img)
				mlx_destroy_image(win->mlx, win->frame->img);
		}
		mlx_destroy_display(win->mlx);
	}
	clear_garbage();
	exit(error_code);
}

t_vector3	str_to_vect(const char *str)
{
	char		**tab;
	t_vector3	vect;

	tab = ft_split(str, ',');
	vect.x = ft_atof(tab[0]);
	vect.y = ft_atof(tab[1]);
	vect.z = ft_atof(tab[2]);
	return (vect);
}

t_color	str_to_rgb(const char *str)
{
	char	**tab;
	t_color	rgb;

	tab = ft_split(str, ',');
	rgb.r = ft_atoi(tab[0]);
	rgb.g = ft_atoi(tab[1]);
	rgb.b = ft_atoi(tab[2]);
	return (rgb);
}
