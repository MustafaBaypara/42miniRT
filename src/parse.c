/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:53:26 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/10 15:41:59 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

static t_scene	*init_scene(t_scene *scene)
{
	scene->al_color = (t_color){255, 255, 255};
	scene->res = (t_size){480, 480};
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
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
	light->ratio = 0.8;
	light->color = (t_color){255, 255, 255};

	sphere->position = (t_vector3){0, 0, 5};
	sphere->radius = 1;
	sphere->color = (t_color){255, 255, 255};

	ft_lstadd_front(&scene->cameras, ft_lstnew(camera));
	ft_lstadd_front(&scene->lights, ft_lstnew(light));
	ft_lstadd_front(&scene->spheres, ft_lstnew(sphere));
	return (scene);
}

int isvalid_rgb(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (str[i] == ',')
		return (0);
	while (str[i])
	{
		if (str[i] == ',')
			j++;
		if (!ft_strchr("0123456789,", str[i]))
				error_exit("Parsing Error.", 1);
		i++;
	}
	if (str[i - 1] == ',')
		return (0);
	if (j != 2)
		return (0);
	return (1);
}

void parse_ambient(t_scene *scene, char **arr)
{
	int i;
	int j;
	int k;
	int rgb[3];

	i = -1;
	j = 0;
	k = 0;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] != NULL)
		error_exit("Parsing Error.", 1);
	scene->al_ratio = ft_atod(arr[1]);
	if (isvalid_rgb(arr[2]) == 0)
		error_exit("Parsing Error.", 1);
	while (arr[2][++i])
	{
		if (arr[2][i] == ',')
		{
			rgb[k] = ft_atoi(ft_substr(arr[2], j, i));
			k++;
			j = i + 1;
		}
	}
	scene->al_color = (t_color){rgb[0], rgb[1], rgb[2]};
}

void parse_camera(t_scene *scene, char **arr)
{
	// kamera parselamada kaldim.
}

void parsing_ext1(t_scene *scene, char **arr)
{
	if (arr == NULL)
		error_exit("Malloc Error.", 1);
	else if (arr[0] == NULL)
		return ;
	else if ((ft_strcmp(arr[0], "A") == 0) && scene->p_control++)
		parse_ambient(scene, arr);
	else if ((ft_strcmp(arr[0], "C") == 0) && scene->p_control++)
		parse_camera(scene, arr);
	else if ((ft_strcmp(arr[0], "L") == 0) && scene->p_control++)
		parse_light(scene, arr);
	else if (ft_strcmp(arr[0], "sp") == 0)
		parse_sphere(scene, arr);
	else if (ft_strcmp(arr[0], "pl") == 0)
		parse_plane(scene, arr);
	else if (ft_strcmp(arr[0], "cy") == 0)
		parse_cylinder(scene, arr);
	else
		error_exit("Parsing Error.", 1);
	
}

t_scene	*parsing(int fd)
{
	t_scene	*scene;
	char	*line;
	int 	i;	

	scene = init_scene(ft_calloc(1, sizeof(t_scene)));
	line = get_next_line(fd);
	i = -1;
	while (line)
	{
		while (line[++i])
		{
			if (!ft_strchr("ACLsplcy0123456789.,+ -\t\n", line[i]))
				error_exit("Parsing Error.", 1);
		}
		parsing_ext1(scene, ft_split(line, ' '));
		line = get_next_line(fd);
		i = -1;
	}
	if (scene->p_control != 3)
		error_exit("Parsing Error.", 1);
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
