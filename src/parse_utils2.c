/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:35:11 by abakirca          #+#    #+#             */
/*   Updated: 2025/03/03 19:40:52 by abakirca         ###   ########.fr       */
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
