/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:25:06 by abakirca          #+#    #+#             */
/*   Updated: 2025/03/05 17:33:51 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_window	*getwindow(void)
{
	static t_window	window;

	return (&window);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = galloc(size);
	if (!ptr)
		error_exit("Malloc failed", 1);
	return (ptr);
}

void	*ft_gcalloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_malloc(count * size);
	ft_bzero(ptr, count * size);
	return (ptr);
}
