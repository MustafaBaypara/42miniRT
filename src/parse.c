/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:53:26 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/06 13:43:17 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

static t_scene	*init_scene(t_scene *scene)
{
	scene->res = (t_size){1280, 1280};
	scene->cameras = ft_lstnew(NULL);
	scene->lights = ft_lstnew(NULL);
	scene->spheres = ft_lstnew(NULL);
	scene->planes = ft_lstnew(NULL);
	scene->cylinders = ft_lstnew(NULL);
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


int	check_line(const char *line, char **data, const char *type, const int nb_elements)
{
	if (!ft_strcmp(data[0], type))
	{
		if (ft_in_charset(line[ft_strlen(type)], " \t"))
			return (ft_tab_size(data) == nb_elements);
	}
	return (0);
}

t_scene	*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		ret;
	char	**data;

	if (!(scene = malloc(sizeof(*scene))))
		print_err_and_exit("Malloc failed", 1);
	if (!(init_scene(scene)))
		return (NULL);
	while ((ret = get_next_line(&line, fd)) == 1)
	{
		data = ft_split_set((*line ? line : "iamcheating"), WHITE_SPACES);
		if (check_line(line, data, "R", NB_ELEM_RESOLUTION) && !scene->resolution.w)
			set_resolution(scene, data);
		else if (check_line(line, data, "A", NB_ELEM_AL) && !scene->al.ratio)
			set_ambient_light(scene, data);
		else if (check_line(line, data, "c", NB_ELEM_CAMERA))
			set_camera(scene, data);
		else if (check_line(line, data, "l", NB_ELEM_LIGHT))
			set_light(scene, data);
		else if (check_line(line, data, "sp", NB_ELEM_SPHERE))
			set_sphere(scene, data);
		else if (check_line(line, data, "pl", NB_ELEM_PLANE))
			set_plane(scene, data);
		else if (check_line(line, data, "sq", NB_ELEM_SQUARE))
			set_square(scene, data);
		else if (check_line(line, data, "cy", NB_ELEM_CYLINDER) || check_line(line, data, "cy", NB_ELEM_CYLINDER + 1))
			set_cylinder(scene, data);
		else if (check_line(line, data, "tr", NB_ELEM_TRIANGLE))
			set_triangle(scene, data);
		else if (!ft_is_from_charset(line, WHITE_SPACES))
		{
			free(line);
			free(data);
			print_err_and_exit("Parse error", PARSE_ERROR);
		}
		free(line);
		free(data);
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
	return (parsing(fd));
}
