/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:03:29 by abakirca          #+#    #+#             */
/*   Updated: 2024/07/08 13:48:23 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)galloc(count * size);
	if (!ptr)
		return (NULL);
	if (size == 1)
		ft_bzero(ptr, size * count);
	else
		ft_memset(ptr, 0, size * count);
	return (ptr);
}
