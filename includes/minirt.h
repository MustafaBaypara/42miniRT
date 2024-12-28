/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:13:02 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/27 17:03:19 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "utils.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>

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
	int			p_control;
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
	void			*mlx;
	void			*win;
	unsigned char	*addr;
	t_frame			*frame;
	t_scene			*scene;
}	t_window;

// Parsing

t_scene		*parse_scene(int argc, char **av);

// Utils
int			quadratic_solver(t_vector3 point, double *a, double *b);
void		error_exit(char *message, int error_code);
double		ft_atod(const char *str);

// Utils tools
float		get_maxf(float a, float b);
float		get_minf(float a, float b);
int			get_maxi(int a, int b);
int			get_mini(int a, int b);

// Frame

void		imaging(t_window *win, t_camera *cam, t_scene *sc, t_impact *imp);

// Vector
t_vector3	new_vec3(double x, double y, double z);
double		distance(t_vector3 a, t_vector3 b);
t_vector3	vec3_norm(t_vector3 v);
t_vector3	vec3_add(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_sub(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_mult(t_vector3 v, double scalar);
double		dot_pd(t_vector3 v1, t_vector3 v2);
t_vector3	cross_product(t_vector3 v1, t_vector3 v2);

// Elements
void		sphere_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj);
void		plane_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj);

// Color
int			color_int(t_color color);
t_color		*set_color(int r, int g, int b);
t_color		object_color(char *type, void *obj);

// Ray
t_ray		new_ray(t_vector3 pos, t_vector3 dir);

#endif
