/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:34:47 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/07 19:21:59 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	len_int(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*res;

	i = 0;
	len = len_int(n);
	res = galloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		i = 1;
	}
	while (len-- > i)
	{
		if (n < 0)
			res[len] = '0' + n % 10 * (-1);
		else
			res[len] = '0' + n % 10;
		n = n / 10;
	}
	return (res);
}
