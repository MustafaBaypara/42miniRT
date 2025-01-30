/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:35:42 by marvin            #+#    #+#             */
/*   Updated: 2025/01/07 19:25:17 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *s1, char *s2, size_t len)
{
	char	*s3;
	int		i;
	int		j;

	j = len;
	i = ft_strlen(s1);
	s3 = (char *)galloc(i + j + 1);
	if (s3 == NULL)
		return (gfree(s1), NULL);
	ft_memcpy(s3, s1, i);
	ft_memcpy(s3 + i, s2, j);
	s3[i + j] = '\0';
	return (s3);
}
