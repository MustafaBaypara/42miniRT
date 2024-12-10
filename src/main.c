/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:25 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/10 17:52:53 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_window	*init_window(t_scene *scene)
{
	t_window	*window;

	window = ft_calloc(1, sizeof(t_window));
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, scene->res.width, scene->res.height, "miniRT");
	window->scene = scene;
	window->frame = ft_calloc(1, sizeof(t_frame));
	window->frame->img = mlx_new_image(window->mlx, scene->res.width, scene->res.height);
	window->frame->addr = mlx_get_data_addr(window->frame->img, &window->frame->bpp, &window->frame->line_len, &window->frame->endian);
	return (window);
}

int	main(int argc, char **av)
{
	t_scene		*scene;
	t_window	*window;

	scene = parse_scene(argc, av);
	window = init_window(scene);
	imaging(window);


	return (0);
}
