/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:48:54 by abakirca          #+#    #+#             */
/*   Updated: 2025/01/07 19:20:48 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	*count_lengths(int *words_len, const char *str, char *charset)
{
	int	i_length;
	int	i_str;

	i_length = 0;
	i_str = 0;
	while (str[i_str])
	{
		while (str[i_str])
		{
			if (!ft_in_charset(str[i_str], charset))
				break ;
			i_str++;
		}
		while (str[i_str])
		{
			if (ft_in_charset(str[i_str], charset))
				break ;
			i_str++;
			words_len[i_length]++;
		}
		i_length++;
	}
	return (words_len);
}

static int	count_words(const char *str, char *charset)
{
	int	count;
	int	i_str;

	count = 0;
	i_str = 0;
	while (str[i_str])
	{
		while (str[i_str])
		{
			if (!ft_in_charset(str[i_str], charset))
			{
				count++;
				break ;
			}
			i_str++;
		}
		while (str[i_str])
		{
			if (ft_in_charset(str[i_str++], charset))
				break ;
		}
	}
	return (count);
}

static int	fill_tab(char **tab, int *words_len, const char *str, char *charset)
{
	int		d1;
	int		d2;
	int		i_str;
	int		words_count;

	d1 = 0;
	i_str = 0;
	words_count = count_words(str, charset);
	while (d1 < words_count && str[i_str])
	{
		tab[d1] = galloc((words_len[d1] + 1) * sizeof(char));
		if (!tab[d1])
			return (0);
		while (ft_in_charset(str[i_str], charset))
			i_str++;
		d2 = 0;
		while (str[i_str] && !ft_in_charset(str[i_str], charset))
			tab[d1][d2++] = str[i_str++];
		tab[d1][d2++] = '\0';
		d1++;
	}
	tab[d1] = 0;
	return (1);
}

char	**ft_split_set(const char *str, char *charset)
{
	char	**tab;
	int		words_count;
	int		*words_len;
	int		i;

	if (!str)
		return (0);
	words_count = count_words(str, charset);
	words_len = galloc((words_count) * sizeof(int));
	if (!words_len)
		return (0);
	words_count = count_words(str, charset);
	tab = galloc((words_count + 1) * sizeof(char *));
	if (!tab)
		return (0);
	i = 0;
	while (i < words_count)
		words_len[i++] = 0;
	count_lengths(words_len, str, charset);
	if (fill_tab(tab, words_len, str, charset))
		return (tab);
	return (0);
}
