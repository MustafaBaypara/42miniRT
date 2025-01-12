/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:53:26 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/11 18:47:39 by mbaypara         ###   ########.fr       */
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
	return (scene);
}

// static t_scene	*temp_scene(t_scene *scene)
// {
// 	t_camera	*camera = ft_calloc(1, sizeof(t_camera));
// 	t_light		*light = ft_calloc(1, sizeof(t_light));
// 	t_sphere	*sphere = ft_calloc(1, sizeof(t_sphere));
// 	t_cylinder	*cylinder = ft_calloc(1, sizeof(t_cylinder));
// 	t_plane		*plane = ft_calloc(1, sizeof(t_plane));

// 	camera->position = (t_vector3){0, 0, 0};
// 	camera->fov = 90;

// 	light->position = (t_vector3){-55, 0, 0};
// 	light->ratio = 0.9 * 255;
// 	light->color = *mult_color_d((t_color){255, 255, 255}, light->ratio);

// 	sphere->pos = (t_vector3){0, 0, -155};
// 	sphere->radius = 50 * 50;
// 	sphere->color = (t_color){255, 255, 255};

// 	scene->al_color = *mult_color_d((t_color){255, 255, 255}, 0.3);

// 	cylinder->pos = (t_vector3){5, 0, -15};
// 	cylinder->dir = vec3_norm((t_vector3){-9, -5, -6});
// 	cylinder->radius = 4 / 2;
// 	cylinder->radius = cylinder->radius * cylinder->radius;
// 	cylinder->height = 5;
// 	cylinder->pos2 = vec3_add(cylinder->pos, vec3_mult(cylinder->dir, cylinder->height));
// 	cylinder->color = (t_color){10, 0, 255};

// 	plane->pos = (t_vector3){0, -5, 0};
// 	plane->normal = vec3_norm((t_vector3){0, 0.1, 0});
// 	plane->color = (t_color){255, 255, 255};

// 	ft_lstadd_front(&(scene->cameras), ft_lstnew(camera));
// 	ft_lstadd_front(&(scene->lights), ft_lstnew(light));
// 	ft_lstadd_front(&(scene->spheres), ft_lstnew(sphere));
// 	ft_lstadd_front(&(scene->cylinders), ft_lstnew(cylinder));
// 	ft_lstadd_front(&(scene->planes), ft_lstnew(plane));
// 	return (scene);
// }

// t_scene	*parsing(int fd)
// {
// 	t_scene	*scene;
// 	char	*line;
// 	char	**data;

// 	scene = init_scene(ft_calloc(1, sizeof(t_scene)));
// 	//line = get_next_line(fd);
// 	return (temp_scene(scene));
// }


static void	set_ambient_light(t_scene *scene, char **data)
{
	t_color	*ambient_light;
	double			ratio;

	if (!(ambient_light = galloc(sizeof(*ambient_light))))
		error_exit("Malloc failed", 1);
	ratio = ft_atof(data[1]);
	*ambient_light = *mult_color_d(str_to_rgb(data[2]), ratio);
	scene->al_color = ambient_light;
	scene->al_ratio = ratio;
}

int	check_line(const char *line, char **data, char *type, const int nb_elements)
{
	if (!ft_strcmp(data[0], type))
	{
		if (ft_in_charset(line[ft_strlen(type)], " \t"))
			return (ft_tab_size(data) == nb_elements);
	}
	return (0);
}

static int ctrl_data_ext(char **data)
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
	else 
		return (0);
}

static int ctrl_data(char **data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		while (data[i][j])
		{
			if (ft_strchr("ACLplscy,.+-0123456789\n", data[i][j]))
				j++;
			else
				return (1);
		}
		i++;
		j = 0;
	}
	return (ctrl_data_ext(data));
}

static int parse_ext(char **data, t_scene *scene, char *line)
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
	else
		return (1);
	return (0);
}

t_scene	*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	char	**data;

	if (!(scene = galloc(sizeof(*scene))))
		error_exit("Malloc failed", 1);
	if (!(init_scene(scene)))
		return (NULL);
	data = NULL;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\0' || line[0] == '\n')
			continue ;
		if (parse_ext(data, scene, line))
			return (NULL);
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
