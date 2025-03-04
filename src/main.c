/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:25 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/04 18:51:14 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	close_window(t_window *window)
{
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_image(window->mlx, window->frame->img);
	mlx_destroy_display(window->mlx);
	clear_garbage();
	printf("Window closed\n");
	exit(0);
	return (0);
}

static t_window	*init_window(t_scene *scene, t_frame *img)
{
	t_size		res;
	t_window	*window;

	window = getwindow();
	res = scene->res;
	window->mlx = addgarbage(mlx_init());
	if (!window->mlx)
		return (NULL);
	window->win = mlx_new_window(window->mlx, res.width, res.height, "minirt");
	if (!window->win)
		return (NULL);
	window->scene = scene;
	window->frame = ft_gcalloc(1, sizeof(t_frame));
	img = window->frame;
	img->img = mlx_new_image(window->mlx, res.width, res.height);
	if (!img->img)
		return (NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
	if (!img->addr)
		return (NULL);
	return (window);
}

int	main(int argc, char **av)
{
	t_scene		*scene;
	t_window	*window;

	scene = parse_scene(argc, av);
	if (!scene)
		error_exit("Parsing failed", 1);
	window = init_window(scene, NULL);
	if (!window)
		error_exit("Window initialization failed", 1);
	mlx_hook(window->win, 17, 1L << 17, close_window, window);
	imaging(window, (t_camera *)scene->cameras->content, scene, NULL);
	mlx_loop(window->mlx);
	return (0);
}
