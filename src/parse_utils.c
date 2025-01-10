/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:27:20 by abakirca          #+#    #+#             */
/*   Updated: 2025/01/10 15:12:01 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int float_checker(char *str)
{
	int i;
	int dot;

	i = 0;
	dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\n')
	{
		if (str[i] == '.')
			dot++;
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (1);
		i++;
	}
	if (dot > 1)
		return (1);
	return (0);
}

int rgb_checker(char *str)
{
	int i;
	int comma;
	int num;

	i = -1;
	comma = 0;
	num = 0;
	while (str[++i] != '\n')
	{
		printf("str[%d] = %c\n", i, str[i]);
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (printf("here\n"), 1);
		if (str[i] == ',')
		{
			comma++;
			num = 0;
		}
		else if (ft_isdigit(str[i]))
			num = num * 10 + (str[i] - '0');
		if (num > 255 || num < 0)
			return (1);
	}
	if (comma != 2)
		return (1);
	return (0);
}

int al_parser(char **data)
{
	if (float_checker(data[1]))
		return (1);
	if (rgb_checker(data[2]))
		return (1);
	if (ft_atof(data[1]) < 0 || ft_atof(data[1]) > 1)
		return (1);
	return (0);	
}

int c_parser(char **data)
{
	int 	i;
	char **strs;

	i = -1;
	strs = ft_split(data[1], ',');
	while (strs[++i])
		if (float_checker(strs[i]))
			return (1);	
	strs = ft_split(data[2], ',');
	i = -1;
	while (strs[++i])
		if (float_checker(strs[i]) && (ft_atof(strs[i]) < 0 || ft_atof(strs[i]) > 1))
			return (1);
	i = -1;
	while (data[3][++i])
		if (!ft_isdigit(data[3][i]))
			return (1);
	if (ft_atoi(data[3]) < 0 || ft_atoi(data[3]) > 180)
		return (1);
	return (0);
}

int l_parser(char **data)
{
	int i;
	char **strs;

	i = -1;
	strs = ft_split(data[1], ',');
	while (strs[++i])
		if (float_checker(strs[i]))
			return (1);
	if (float_checker(data[2]) && (ft_atof(data[2]) < 0 || ft_atof(data[2]) > 1))
		return (1);
	if (rgb_checker(data[3]))
		return (1);
	return (0);
}
