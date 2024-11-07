/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:49:30 by abakirca          #+#    #+#             */
/*   Updated: 2024/07/08 13:45:21 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_garbcol	**getgarbage(void) // Program boyunca kullanılacak garbage collector'ü döndürür
{
	static t_garbcol	*collector;

	return (&collector);
}
