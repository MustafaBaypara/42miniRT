/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:10:29 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/03 19:40:37 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_ambient_light(t_scene *scene, char **data)
{
	t_color	*ambient_light;
	double	ratio;

	ambient_light = ft_malloc(sizeof(*ambient_light));
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

int	parse_ext(char **data, t_scene *scene, char *line)
{
	line = ft_strtrim(line, " \t\n");
	data = ft_split_set(line, " \t");
	if (!data)
		error_exit("Malloc failed", 1);
	if (ctrl_data(data))
		return (1);
	if (check_line(line, data, "A", 3))
		set_ambient_light(scene, data);
	else if (check_line(line, data, "C", 4) && check_comma(data, 2))
		set_camera(scene, data);
	else if (check_line(line, data, "L", 4) && check_comma(data, 1))
		set_light(scene, data);
	else if (check_line(line, data, "sp", 4) && check_comma(data, 1))
		set_sphere(scene, data);
	else if (check_line(line, data, "pl", 4) && check_comma(data, 2))
		set_plane(scene, data);
	else if (check_line(line, data, "cy", 6) && check_comma(data, 2))
		set_cylinder(scene, data);
	else
		return (1);
	return (0);
}
