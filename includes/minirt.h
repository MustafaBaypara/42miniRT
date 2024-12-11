/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:13:02 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/11 18:05:36 by mbaypara         ###   ########.fr       */
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
	int		len;
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

void		error_exit(char *message, int error_code);

// Parsing

t_scene		*parse_scene(int argc, char **av);

// Utils
int			quadratic_solver(t_vector3 point, double *a, double *b);
t_color		*set_color(int r, int g, int b);

// Frame

void		imaging(t_window *win, t_camera *cam, t_scene *sc, t_impact *imp);

// Vector
t_vector3	new_vec3(double x, double y, double z);
double		distance(t_vector3 a, t_vector3 b);
t_vector3	vec3_op(t_vector3 v1, t_vector3 v2, double scalar, char op);
double		dot_product(t_vector3 v1, t_vector3 v2);
t_vector3	cross_product(t_vector3 v1, t_vector3 v2);

// Elements
void		sphere_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj);

#endif