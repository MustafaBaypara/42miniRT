/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:13:02 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/10 17:56:48 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "utils.h"
# include "libft.h"
# include "mlx.h"

typedef struct s_scene
{
	t_size		res;
	double		al_ratio;
	t_color		al_color;
	t_list		*cameras;
	t_list		*lights;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}	t_scene;

typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_frame;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_frame	*frame;
	t_scene	*scene;
}	t_window;

// Utils

void	error_exit(char *message, int error_code);

// Parsing

t_scene	*parse_scene(int argc, char **av);

// Utils

t_color	*set_color(int r, int g, int b);

// Frame

void	imaging(t_window *window);

#endif