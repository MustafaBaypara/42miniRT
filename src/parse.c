/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:53:26 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/30 17:06:24 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

static t_scene	*init_scene(t_scene *scene)
{
	scene->res = (t_size){480, 480};
	scene->cameras = ft_lstnew(NULL);
	scene->lights = ft_lstnew(NULL);
	scene->spheres = ft_lstnew(NULL);
	scene->planes = ft_lstnew(NULL);
	scene->cylinders = ft_lstnew(NULL);
	return (scene);
}

static t_scene	*temp_scene(t_scene *scene)
{
	t_camera	*camera = ft_calloc(1, sizeof(t_camera));
	t_light		*light = ft_calloc(1, sizeof(t_light));
	t_sphere	*sphere = ft_calloc(1, sizeof(t_sphere));

	camera->position = (t_vector3){0, 0, 0};
	camera->fov = 90;

	light->position = (t_vector3){-20, 0, -10};
	light->ratio = 0.8 * 255;
	light->color = *mult_color_d((t_color){255, 255, 255}, light->ratio);

	sphere->position = (t_vector3){0, 0, -7};
	sphere->radius = 3 * 3;
	sphere->color = (t_color){255, 255, 255};

	scene->al_color = *mult_color_d((t_color){255, 255, 255}, 0.3);

	ft_lstadd_front(&(scene->cameras), ft_lstnew(camera));
	ft_lstadd_front(&(scene->lights), ft_lstnew(light));
	ft_lstadd_front(&(scene->spheres), ft_lstnew(sphere));
	return (scene);
}

t_scene	*parsing(int fd)
{
	t_scene	*scene;
	char	*line;
	char	**data;

	scene = init_scene(ft_calloc(1, sizeof(t_scene)));
	//line = get_next_line(fd);
	return (temp_scene(scene));
}

t_scene	*parse_scene(int argc, char **av)
{
	int		fd;

	if (argc < 2)
		error_exit("No scene file provided", 1);
	if (argc > 3)
		error_exit("Expecting 2 arguments", 1);
	if (argc == 2 && ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3))
		error_exit("Invalid scene file, must be a .rt file", 1);
	fd = open(av[1], O_RDONLY);
	if ((fd) < 0)
		error_exit("Failed to open scene file", 1);
	return (parsing(fd));
}
