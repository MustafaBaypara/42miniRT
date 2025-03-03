/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:53:26 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/04 00:07:16 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

static t_scene	*init_scene(t_scene *scene)
{
	scene->res = (t_size){720, 720};
	scene->cameras = ft_lstnew(NULL);
	if (!scene->cameras)
		return (NULL);
	scene->lights = ft_lstnew(NULL);
	if (!scene->lights)
		return (NULL);
	scene->spheres = ft_lstnew(NULL);
	if (!scene->spheres)
		return (NULL);
	scene->planes = ft_lstnew(NULL);
	if (!scene->planes)
		return (NULL);
	scene->cylinders = ft_lstnew(NULL);
	if (!scene->cylinders)
		return (NULL);
	scene->triangles = ft_lstnew(NULL);
	if (!scene->triangles)
		return (NULL);
	return (scene);
}

t_scene	*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	char	**data;

	scene = ft_malloc(sizeof(*scene));
	if (!(init_scene(scene)))
		return (NULL);
	data = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\0' || line[0] == '\n')
		{
			line = get_next_line(fd);
			continue ;
		}
		if (parse_ext(data, scene, line))
			return (NULL);
		line = get_next_line(fd);
	}
	return (scene);
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
	return (parse(fd));
}

int	check_comma(char **data, int flag)
{
	int	i;
	int	j;
	int	comma;

	i = 1;
	j = 0;
	comma = 0;
	while (i < flag + 1)
	{
		while (data[i][j])
		{
			if (data[i][j] == ',')
				comma++;
			j++;
		}
		if (comma != 2)
			return (0);
		i++;
		j = 0;
		comma = 0;
	}
	return (1);
}
