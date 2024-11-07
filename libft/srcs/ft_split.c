/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:36:05 by abakirca          #+#    #+#             */
/*   Updated: 2024/07/11 15:42:48 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>
static char	**merror(char **arr, size_t i)
{
	while (arr[i])
		gfree(arr[i++]);
	gfree(arr);
	return (NULL);
}

static int	word_counter(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (i);
}

static int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	if (!*s)
		return (0);
	while (*s && *s++ != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		a;
	int		i;

	a = -1;
	i = 0;
	res = (char **)galloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!s || !res)
		return (NULL);
	while (++a < word_counter(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		res[a] = ft_substr(s, i, word_len(&s[i], c));
		if (!res[a])
			return (merror(res, 0));
		i += word_len(&s[i], c);
	}
	res[a] = NULL;
	return (res);
}
