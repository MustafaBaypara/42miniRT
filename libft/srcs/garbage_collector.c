/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:48:33 by abakirca          #+#    #+#             */
/*   Updated: 2024/07/08 13:48:40 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "stdbool.h"

static bool	free_from_ll(void *address) // GC'de istenen adresi freeleme ve listeden çıkarma
{
	t_garbcol	*todel;

	todel = *getgarbage();
	while (todel && address)
	{
		if (todel->content == address)
		{
			if (todel->previous)
			{
				todel->previous->next = todel->next;
				todel->next->previous = todel->previous;
			}
			else
			{
				todel->next->previous = 0;
				*getgarbage() = todel->next;
			}
			free(todel->content);
			free(todel);
			return (true);
		}
		todel = todel->next;
	}
	return (false);
}

void	gfree(void *address) //GC'de istenen adresi freeleme
{
	if (address && !GARBAGE_COLLECTOR)
		free(address);
	else if (!address || !GARBAGE_COLLECTOR)
		return ;
	else if (!free_from_ll(address))
		free(address);
}

void	*addgarbage(void *address) //GC'ye adres ekleme
{
	t_garbcol	**collector;
	t_garbcol	*tmp;

	if (!address)
		return (0);
	if (!GARBAGE_COLLECTOR)
		return (address);
	collector = getgarbage();
	tmp = (t_garbcol *)malloc(sizeof(t_garbcol));
	if (!tmp)
		return (0);
	tmp->next = 0;
	tmp->previous = 0;
	tmp->content = address;
	if (*collector)
	{
		tmp->next = *collector;
		tmp->next->previous = tmp;
		*collector = tmp;
	}
	else
		*collector = tmp;
	return (tmp->content);
}

void	*galloc(size_t size) // Mallocla yer açıp, adresi GC'ye ekleme
{
	void	*address;

	address = addgarbage(malloc(size));
	return (address);
}

void	clear_garbage(void) //Bütün GC'yi temizleme
{
	t_garbcol	**collector;
	t_garbcol	*todel;
	t_garbcol	*tmp;

	collector = getgarbage();
	todel = *collector;
	while (todel)
	{
		free(todel->content);
		tmp = todel->next;
		free(todel);
		todel = tmp;
	}
	*collector = 0;
}
