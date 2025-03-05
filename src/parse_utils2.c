/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:35:11 by abakirca          #+#    #+#             */
/*   Updated: 2025/03/05 17:33:56 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sp_parser(char **data)
{
	int		i;
	char	**strs;

	i = -1;
	strs = ft_split(data[1], ',');
	if (!strs)
		return (1);
	while (strs[++i])
		if (float_checker(strs[i]))
			return (1);
	if (float_checker(data[2]) || ft_atof(data[2]) < 0)
		return (1);
	if (rgb_checker(data[3]))
		return (1);
	return (0);
}

int	pl_parser(char **data)
{
	int		i;
	char	**strs;

	i = -1;
	strs = ft_split(data[1], ',');
	if (!strs)
		return (1);
	while (strs[++i])
		if (float_checker(strs[i]))
			return (1);
	strs = ft_split(data[2], ',');
	if (!strs)
		return (1);
	i = -1;
	while (strs[++i])
		if (float_checker(strs[i]) || (ft_atof(strs[i]) < -1
				|| ft_atof(strs[i]) > 1))
			return (1);
	if (rgb_checker(data[3]))
		return (1);
	return (0);
}

int	cy_parser(char **data)
{
	int		i;
	char	**strs;

	i = -1;
	strs = ft_split(data[1], ',');
	if (!strs)
		return (1);
	while (strs[++i])
		if (float_checker(strs[i]))
			return (1);
	strs = ft_split(data[2], ',');
	if (!strs)
		return (1);
	i = -1;
	while (strs[++i])
		if (float_checker(strs[i]) || (ft_atof(strs[i]) < -1
				|| ft_atof(strs[i]) > 1))
			return (1);
	if (float_checker(data[3]) || ft_atof(data[3]) < 0)
		return (1);
	if (float_checker(data[4]) || ft_atof(data[4]) < 0)
		return (1);
	if (rgb_checker(data[5]))
		return (1);
	return (0);
}

static int	tr_parser_ext(char **data)
{
	int		i;
	char	**strs;

	strs = ft_split(data[3], ',');
	if (!strs)
		return (1);
	i = -1;
	while (strs[++i])
		if (float_checker(strs[i]))
			return (1);
	if (rgb_checker(data[4]))
		return (1);
	return (0);
}

int	tr_parser(char **data)
{
	int		i;
	char	**strs;

	i = -1;
	strs = ft_split(data[1], ',');
	if (!strs)
		return (1);
	while (strs[++i])
		if (float_checker(strs[i]))
			return (1);
	strs = ft_split(data[2], ',');
	if (!strs)
		return (1);
	i = -1;
	while (strs[++i])
		if (float_checker(strs[i]))
			return (1);
	if (tr_parser_ext(data))
		return (1);
	return (0);
}
