/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:16:08 by abakirca          #+#    #+#             */
/*   Updated: 2024/07/08 13:48:23 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newcontent;

	newcontent = (t_list *)galloc(sizeof(t_list));
	if (!newcontent)
		return (NULL);
	newcontent->content = content;
	newcontent->next = NULL;
	return (newcontent);
}
