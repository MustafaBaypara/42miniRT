/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:25 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/07 17:48:54 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int close_window(t_window *window)
{
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_image(window->mlx, window->frame->img);
	free(window->frame);
	free(window->scene);
	free(window);
	exit(0);
	return (0);
}

static t_window	*init_window(t_scene *scene)
{
	t_window	*window;
	t_size		res;
	t_frame		*img;

	res = scene->res;
	window = ft_calloc(1, sizeof(t_window));
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, res.width, res.height, "miniRT");
	window->scene = scene;
	window->frame = ft_calloc(1, sizeof(t_frame));
	img = window->frame;
	img->img = mlx_new_image(window->mlx, res.width, res.height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
	return (window);
}

int	main(int argc, char **av)
{
	t_scene		*scene;
	t_window	*window;

	scene = parse_scene(argc, av);
	printf("Al settings -> [%f] - [%d,%d,%d]\n", scene->al_ratio, scene->al_color->r, scene->al_color->g, scene->al_color->b);
	printf("C settings -> [%f,%f,%f] - [%f,%f,%f] - [%f]\n", ((t_camera *)scene->cameras->content)->position.x, ((t_camera *)scene->cameras->content)->position.y, ((t_camera *)scene->cameras->content)->position.z, ((t_camera *)scene->cameras->content)->orientation.x, ((t_camera *)scene->cameras->content)->orientation.y, ((t_camera *)scene->cameras->content)->orientation.z, ((t_camera *)scene->cameras->content)->fov);
	printf("L settings -> [%f,%f,%f] - [%f] - [%d,%d,%d]\n", ((t_light *)scene->lights->content)->position.x, ((t_light *)scene->lights->content)->position.y, ((t_light *)scene->lights->content)->position.z, ((t_light *)scene->lights->content)->ratio, ((t_light *)scene->lights->content)->color.r, ((t_light *)scene->lights->content)->color.g, ((t_light *)scene->lights->content)->color.b);
	printf("Pl settings -> [%f,%f,%f] - [%f,%f,%f] - [%d,%d,%d]\n", ((t_plane *)scene->planes->content)->pos.x, ((t_plane *)scene->planes->content)->pos.y, ((t_plane *)scene->planes->content)->pos.z, ((t_plane *)scene->planes->content)->normal.x, ((t_plane *)scene->planes->content)->normal.y, ((t_plane *)scene->planes->content)->normal.z, ((t_plane *)scene->planes->content)->color.r, ((t_plane *)scene->planes->content)->color.g, ((t_plane *)scene->planes->content)->color.b);
	printf("Sp settings -> [%f,%f,%f] - [%f] - [%d,%d,%d]\n", ((t_sphere *)scene->spheres->content)->pos.x, ((t_sphere *)scene->spheres->content)->pos.y, ((t_sphere *)scene->spheres->content)->pos.z, ((t_sphere *)scene->spheres->content)->radius, ((t_sphere *)scene->spheres->content)->color.r, ((t_sphere *)scene->spheres->content)->color.g, ((t_sphere *)scene->spheres->content)->color.b);
	printf("Cy settings -> [%f,%f,%f] - [%f,%f,%f] - [%f] - [%f] - [%d,%d,%d]\n", ((t_cylinder *)scene->cylinders->content)->pos.x, ((t_cylinder *)scene->cylinders->content)->pos.y, ((t_cylinder *)scene->cylinders->content)->pos.z, ((t_cylinder *)scene->cylinders->content)->dir.x, ((t_cylinder *)scene->cylinders->content)->dir.y, ((t_cylinder *)scene->cylinders->content)->dir.z, ((t_cylinder *)scene->cylinders->content)->radius, ((t_cylinder *)scene->cylinders->content)->height, ((t_cylinder *)scene->cylinders->content)->color.r, ((t_cylinder *)scene->cylinders->content)->color.g, ((t_cylinder *)scene->cylinders->content)->color.b);
	window = init_window(scene);
	imaging(window, (t_camera *)scene->cameras->content, scene, NULL);
	mlx_put_image_to_window(window->mlx, window->win, window->frame->img, 0, 0);
	mlx_hook(window->win, 17, 1L<<17, close_window, window);
	mlx_loop(window->mlx);

	return (0);
}
