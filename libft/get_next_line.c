/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:05:33 by mbaypara          #+#    #+#             */
/*   Updated: 2025/01/07 19:25:25 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	*free_stash(char **stash, int cline);

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

static void	*free_stash(char **stash, int cline)
{
	char	*line;

	if (!*stash)
		return (NULL);
	if (cline == 0)
	{
		if (*stash)
		{
			gfree(*stash);
			*stash = NULL;
		}
		return (NULL);
	}
	else if (cline == 1)
	{
		line = ft_strdup(*stash);
		gfree(*stash);
		*stash = NULL;
		return (line);
	}
	return (NULL);
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
	nl = galloc(i + 2);
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
