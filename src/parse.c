/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:53:26 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/06 17:16:03 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

static t_scene	*init_scene(t_scene *scene)
{
	scene->size.width = 0;
	scene->size.height = 0;
	scene->ambient.r = 0;
	scene->ambient.g = 0;
	scene->ambient.b = 0;
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	return (scene);
}

t_scene	*parsing(int fd)
{
	t_scene	*scene;
	char	*line;
	char	**data;

	scene = init_scene(ft_calloc(1, sizeof(t_scene)));
	while (get_next_line(fd))
	{
		return (scene);
	}
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
