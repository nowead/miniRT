/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:18:20 by damin             #+#    #+#             */
/*   Updated: 2023/10/26 20:46:18 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *str, char c)
{
	size_t	i;
	size_t	j;
	size_t	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] == c)
			++i;
		j = i;
		while (str[i] != c && str[i])
			++i;
		if (i > j)
			++wc;
	}
	return (wc);
}

static void	*free_all(char **strs, size_t x)
{
	size_t	i;

	i = 0;
	while (i <= x)
	{
		free(strs[i]);
		++i;
	}
	free(strs);
	return (NULL);
}

static char	**make_strs(char **strs, char const *str, char c, size_t wc)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		while (str[i] == c)
			++i;
		j = i;
		while (str[i] != c && str[i])
			++i;
		if (i <= j)
			continue ;
		strs[x] = (char *)malloc((i - j + 1) * sizeof(char));
		if (strs[x] == NULL)
		{
			free_all(strs, x);
			return (NULL);
		}
		ft_strlcpy(strs[x++], &str[j], i - j + 1);
	}
	strs[wc] = NULL;
	return (strs);
}

char	**ft_split(char const *str, char c)
{
	size_t		wc;
	char		**strs;

	if (!str)
		return (NULL);
	wc = word_count(str, c);
	strs = (char **)malloc((wc + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs = make_strs(strs, str, c, wc);
	return (strs);
}
