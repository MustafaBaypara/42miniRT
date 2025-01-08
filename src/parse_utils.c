/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:27:20 by abakirca          #+#    #+#             */
/*   Updated: 2025/01/08 19:03:15 by abakirca         ###   ########.fr       */
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
	while (str[i])
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

	i = 0;
	comma = 0;
	num = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (1);
		if (str[i] == ',')
		{
			comma++;
			num = 0;
		}
		else if (ft_isdigit(str[i]))
			num = num * 10 + (str[i] - '0');
		if (num > 255 || num < 0)
			return (1);
		i++;
	}
	if (comma != 2)
		return (1);
	return (0);
}

int	is_invalid_sign(char c, char prev_char)
{
	if ((c == '+' || c == '-') && (prev_char == '+' || prev_char == '-' 
		|| prev_char == '.'))
		return (1);
	return (0);
}

int	is_invalid_dot(char c, char prev_char, int *dot_count, int *digits_after_dot)
{
	if (c == '.')
	{
		if (*dot_count >= 3 || *digits_after_dot > 3 || prev_char == '.' 
			|| prev_char == ',' || prev_char == '\0')
			return (1);
		(*dot_count)++;
		*digits_after_dot = 0;
	}
	return (0);
}

int	is_invalid_comma(char c, char prev_char)
{
	if (c == ',' && (prev_char == ',' || prev_char == '+' 
		|| prev_char == '-' || prev_char == '.'))
		return (1);
	return (0);
}

int	check_comma_and_dot(char c, char prev_char, int *comma_count, int *dot_count)
{
	if (c == ',')
	{
		if (prev_char == ',' || prev_char == '+' || prev_char == '-' || prev_char == '.')
			return (1);
		(*comma_count)++;
		*dot_count = 0;
	}
	return (0);
}

int	process_digit_and_sign(char c, char prev_char, int *consecutive_signs, int dot_count, int *digits_after_dot)
{
	if (c == '+' || c == '-')
	{
		if (prev_char == '+' || prev_char == '-' || prev_char == '.')
			return (1);
		(*consecutive_signs)++;
	}
	else if (isdigit(c))
	{
		*consecutive_signs = 0;
		if (dot_count > 0)
			(*digits_after_dot)++;
	}
	return (0);
}

int	is_validcoords(const char *coord)
{
	int	i;
	int	comma_count;
	int	dot_count;
	int	consecutive_signs;
	int	prev_char;
	int	digits_after_dot;

	i = 0;
	comma_count = 0;
	dot_count = 0;
	consecutive_signs = 0;
	prev_char = 0;
	digits_after_dot = 0;
	while (coord[i] != '\0')
	{
		if (process_digit_and_sign(coord[i], prev_char, &consecutive_signs, dot_count, &digits_after_dot)
			|| is_invalid_dot(coord[i], prev_char, &dot_count, &digits_after_dot)
			|| check_comma_and_dot(coord[i], prev_char, &comma_count, &dot_count))
			return (1);
		prev_char = coord[i++];
	}
	if (comma_count != 2 || dot_count > 3 || consecutive_signs > 1 || digits_after_dot > 3)
		return (1);
	return (0);
}

int al_parser(char **data, int nb_elements)
{
	if (ft_tab_size(data) != nb_elements)
		return (1);
	if (ft_strlen(data[1]) >= 11 && float_checker(data[1]))
		return (1);
	if (ft_strlen(data[2]) >= 12 && rgb_checker(data[2]))
		return (1);
	if (ft_atof(data[1]) < 0 || ft_atof(data[1]) > 1)
		return (1);
	return (0);	
}

int c_parser(char **data, int nb_elements)
{
	int i;

	i = 0;
	if (ft_tab_size(data) != nb_elements)
		return (1);
	if (is_validcoords)
	
	return (0);
}
