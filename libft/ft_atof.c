/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:11:33 by abakirca          #+#    #+#             */
/*   Updated: 2025/01/07 17:22:53 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

float	ft_atof(const char *str)
{
	int		decimal_size;
	float	nb;
	int		sign;

	while (ft_in_charset(*str, "\t "))
		str++;
	sign = 1;
	if ((*str == '+' || *str == '-') && *str++ == '-')
		sign *= -1;
	nb = 0;
	nb += ft_atol(str);
	while (*str && ft_in_charset(*str, "0123456789"))
		str++;
	if (*str == '.')
		str++;
	else
		return (nb * sign);
	decimal_size = 0;
	while (ft_in_charset(str[decimal_size], "0123456789"))
		decimal_size++;
	if (decimal_size)
		nb += ft_atol(str) / (pow(10, decimal_size)); // ft_pow vardi.
	else
		return (nb * sign);
	return (nb * sign);
}
