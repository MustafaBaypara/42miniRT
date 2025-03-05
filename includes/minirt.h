/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:13:02 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/05 17:31:16 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "utils.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

typedef struct s_scene
{
	t_size		res;
	t_color		*al_color;
	double		al_ratio;
	t_list		*cameras;
	t_list		*lights;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
	t_list		*triangles;
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
	t_frame			*frame;
	t_scene			*scene;
}	t_window;

typedef struct s_lighting
{
	t_ray		ray_to_light;
	void		*obstacle;
	double		dot_light;
	t_color		color_l;
	t_color		diffuse;
}	t_lighting;

// Parsing

t_scene		*parse_scene(int argc, char **av);
int			parse_ext(char **data, t_scene *scene, char *line);
void		set_camera(t_scene *scene, char **data);
void		set_light(t_scene *scene, char **data);
void		set_sphere(t_scene *scene, char **strs);
void		set_plane(t_scene *scene, char **strs);
void		set_cylinder(t_scene *scene, char **strs);
void		set_triangle(t_scene *scene, char **strs);
int			float_checker(char *str);
int			rgb_checker(char *str);
int			al_parser(char **data);
int			c_parser(char **data);
int			l_parser(char **data);
int			sp_parser(char **data);
int			pl_parser(char **data);
int			cy_parser(char **data);
int			tr_parser(char **data);

// Utils
int			quadratic_solver(t_vector3 point, double *a, double *b);
void		error_exit(char *message, int error_code);
t_vector3	str_to_vect(const char *str);
t_color		str_to_rgb(const char *str);
t_window	*getwindow(void);
void		*ft_malloc(size_t size);
void		*ft_gcalloc(size_t count, size_t size);
int			check_comma(char **data, int flag);

// Utils tools
float		get_maxf(float a, float b);
float		get_minf(float a, float b);
int			get_maxi(int a, int b);
int			get_mini(int a, int b);

// Frame

void		imaging(t_window *win, t_camera *cam, t_scene *sc, t_impact *imp);
t_impact	*check_objects(t_ray ray, t_scene *scene, void **object);

// Vector
t_vector3	new_vec3(double x, double y, double z);
double		distance(t_vector3 a, t_vector3 b);
t_vector3	vec3_norm(t_vector3 v);
t_vector3	vec3_add(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_sub(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_mult(t_vector3 v, double scalar);
t_vector3	vec3_minus(t_vector3 v1);
double		dot_pd(t_vector3 v1, t_vector3 v2);

// Elements
void		triangle_ray(t_ray ray, t_scene *scene,
				t_impact *impact, void **obj);
void		sphere_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj);
void		plane_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj);
void		cyl_ray(t_ray ray, t_scene *scene, t_impact *impact, void **obj);
void		calc_normal(double a[2], t_cylinder cyl, double d1, double d2);
int			solve_cyl(double a[2], t_ray ray, t_cylinder cyl);
double		solve_pl(t_vector3 origin, t_vector3 dir,
				t_vector3 pos, t_vector3 n);
double		isec_cap(t_ray ray, t_cylinder cyl, double d1, double d2);
double		isec_side(t_ray ray, t_cylinder cyl);

// Color
int			color_int(t_color color);
t_color		*int_color(int r, int g, int b);
t_color		object_color(char *type, void *obj);
t_color		*mult_color(t_color color, t_color color2);
t_color		*mult_color_d(t_color color, double d);
t_color		*add_color(t_color color, t_color color2);
void		min_color(t_color *color);

// Ray
t_ray		new_ray(t_vector3 pos, t_vector3 dir);
t_ray		generate_ray(t_camera *camera, t_size res, int i, int j);

// Light
t_color		*lighting(t_scene *sc, t_impact *imp, t_color *color);

#endif