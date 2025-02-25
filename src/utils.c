/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:54:43 by mbaypara          #+#    #+#             */
/*   Updated: 2025/02/25 21:12:17 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// func_swap swaps the values of two pointers
static void	func_swap(void *a, void *b)
{
	void	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

// quadratic_solver solves the quadratic equation that is used for the intersection of the ray and the object
int	quadratic_solver(t_vector3 point, double *a, double *b)
{
	double	discriminant;
	double	q;

	discriminant = point.y * point.y - 4 * point.x * point.z; // calculate the discriminant
	if (discriminant < 0) // if the discriminant is less than 0, return 0
		return (0);
	else if (discriminant == 0) // if the discriminant is 0, set a and b to the same value		
	{
		*a = -0.5 * point.y / point.x;
		*b = -0.5 * point.y / point.x;
	}
	else // if the discriminant is greater than 0, solve the quadratic equation
	{
		if (point.y > 0) // if the y value of the point is greater than 0, set q to the negative of the y value plus the square root of the discriminant
			q = -0.5 * (point.y + sqrt(discriminant));
		else // if the y value of the point is less than 0, set q to the negative of the y value minus the square root of the discriminant
			q = -0.5 * (point.y - sqrt(discriminant));
		*a = q / point.x; // set a to q divided by the x value of the point
		*b = point.z / q; // set b to the z value of the point divided by q
	}
	if (*a > *b) // if a is greater than b, swap the values of a and b
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
