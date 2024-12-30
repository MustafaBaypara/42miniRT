/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:25 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/30 14:35:06 by mbaypara         ###   ########.fr       */
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
	window = init_window(scene);
	imaging(window, (t_camera *)scene->cameras->content, scene, NULL);
	mlx_put_image_to_window(window->mlx, window->win, window->frame->img, 0, 0);
	mlx_hook(window->win, 17, 1L<<17, close_window, window);
	mlx_loop(window->mlx);

	return (0);
}
