/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:05:33 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/06 17:20:13 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static char	*copy_stash(char *stash, char *buffer)
{
	char	*res;

	res = 0;
	if (!stash && buffer)
	{
		res = ft_strdup(buffer);
		if (!res)
			return (NULL);
		return (res);
	}
	res = ft_strjoin(stash, buffer);
	free_stash(&stash, 0);
	return (res);
}

static int	have_nl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i] != '\0')
		if (s[i] == '\n')
			return (1);
	return (0);
}

static char	*line_extract(char *stash)
{
	char	*nl;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i] != '\n')
		i++;
	nl = malloc(i + 2);
	if (!nl)
		return (0);
	j = 0;
	while (j < i + 1)
	{
		nl[j] = stash[j];
		j++;
	}
	nl[j] = '\0';
	return (nl);
}

static char	*recreate_stash(char *stash)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n')
		i++;
	if (stash[i + 1] == '\0')
		return (free_stash(&stash, 0));
	res = ft_substr(stash, i + 1, ft_strlen(stash));
	if (!res)
	{
		free_stash(&stash, 0);
		return (NULL);
	}
	free_stash(&stash, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		readed;
	static char	*stash = NULL;
	char		*nl;

	nl = NULL;
	readed = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_stash(&stash, 0));
	while (readed)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if ((readed <= 0 && !stash) || readed == -1)
			return (free_stash(&stash, 0));
		buffer[readed] = '\0';
		stash = copy_stash(stash, buffer);
		if (have_nl(stash))
		{
			nl = line_extract(stash);
			if (!nl)
				return (free_stash(&stash, 0));
			return (stash = recreate_stash(stash), nl);
		}
	}
	return (free_stash(&stash, 1));
}
