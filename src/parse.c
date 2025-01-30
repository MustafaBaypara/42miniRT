/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:53:26 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/17 06:04:08 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

static t_scene	*init_scene(t_scene *scene)
{
	scene->res = (t_size){1280, 1280};
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

static void	set_ambient_light(t_scene *scene, char **data)
{
	t_color	*ambient_light;
	double	ratio;

	ambient_light = galloc(sizeof(*ambient_light));
	if (!ambient_light)
		error_exit("Malloc failed", 1);
	ratio = ft_atof(data[1]);
	*ambient_light = *mult_color_d(str_to_rgb(data[2]), ratio);
	scene->al_color = ambient_light;
	scene->al_ratio = ratio;
}

static int	check_line(const char *l, char **data, char *type, const int nb_e)
{
	if (!ft_strcmp(data[0], type))
	{
		if (ft_in_charset(l[ft_strlen(type)], " \t"))
			return (ft_tab_size(data) == nb_e);
	}
	return (0);
}

static int	ctrl_data_ext(char **data)
{
	if (ft_strcmp(data[0], "A") == 0)
		return (al_parser(data));
	else if (ft_strcmp(data[0], "C") == 0)
		return (c_parser(data));
	else if (ft_strcmp(data[0], "L") == 0)
		return (l_parser(data));
	else if (ft_strcmp(data[0], "sp") == 0)
		return (sp_parser(data));
	else if (ft_strcmp(data[0], "pl") == 0)
		return (pl_parser(data));
	else if (ft_strcmp(data[0], "cy") == 0)
		return (cy_parser(data));
	else if (ft_strcmp(data[0], "tr") == 0)
		return (tr_parser(data));
	else
		return (0);
}

static int	ctrl_data(char **data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		while (data[i][j])
		{
			if (ft_strchr("ACLplscytr,.+-0123456789\n", data[i][j]))
				j++;
			else
				return (1);
		}
		i++;
		j = 0;
	}
	return (ctrl_data_ext(data));
}

static int	parse_ext(char **data, t_scene *scene, char *line)
{
	line = ft_strtrim(line, " \t\n");
	data = ft_split_set(line, " \t");
	if (!data)
		error_exit("Malloc failed", 1);
	if (ctrl_data(data))
		return (1);
	if (check_line(line, data, "A", 3))
		set_ambient_light(scene, data);
	else if (check_line(line, data, "C", 4))
		set_camera(scene, data);
	else if (check_line(line, data, "L", 4))
		set_light(scene, data);
	else if (check_line(line, data, "sp", 4))
		set_sphere(scene, data);
	else if (check_line(line, data, "pl", 4))
		set_plane(scene, data);
	else if (check_line(line, data, "cy", 6))
		set_cylinder(scene, data);
	else if (check_line(line, data, "tr", 5))
		set_triangle(scene, data);
	else
		return (1);
	return (0);
}

t_scene	*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	char	**data;

	scene = galloc(sizeof(*scene));
	if (!scene)
		error_exit("Malloc failed", 1);
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
