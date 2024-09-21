/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:34:57 by seonseo           #+#    #+#             */
/*   Updated: 2024/09/21 20:24:54 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_sep(int c, char const *charset);
static size_t	ft_wordcount(char const *s, char const *charset);
static int		ft_wordlen(char const *s, char const *charset, char **strs);
static int		ft_wordcpy(char const *s, char const *start, char **strs);

char	**ft_split(char const *s, char const *charset)
{
	char	**strs;
	size_t	wordcount;
	char	**strs_p;

	if (s == NULL)
		return (NULL);
	wordcount = ft_wordcount((char *)s, charset);
	strs = (char **)ft_calloc(wordcount + 1, sizeof(char *));
	if (strs == NULL)
		return (NULL);
	if (ft_wordlen((char *)s, charset, strs))
	{
		strs_p = strs;
		while (*strs_p)
		{
			free(*strs_p);
			strs_p++;
		}
		free (strs);
		return (NULL);
	}
	return (strs);
}

static int	is_sep(int c, char const *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (c == (int)charset[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_wordcount(char const *s, char const *charset)
{
	size_t	wordcount;
	int		is_word;

	wordcount = 0;
	is_word = 0;
	while (*s)
	{
		if (!is_sep((int)*s, charset) && is_word == 0)
		{
			is_word = 1;
			wordcount++;
		}
		if (is_sep((int)*s, charset) && is_word == 1)
			is_word = 0;
		s++;
	}
	return (wordcount);
}

static int	ft_wordlen(char const *s, char const *charset, char **strs)
{
	char const	*start;

	start = NULL;
	while (*s)
	{
		if (!is_sep((int)*s, charset) && start == NULL)
			start = s;
		else if (is_sep((int)*s, charset) && start != NULL)
		{
			if (ft_wordcpy(s, start, strs))
				return (1);
			strs++;
			start = NULL;
		}
		s++;
	}
	if (start != NULL && ft_wordcpy(s, start, strs))
		return (1);
	return (0);
}

static int	ft_wordcpy(char const *s, char const *start, char **strs)
{
	*strs = (char *)malloc(sizeof(char) * (s - start + 1));
	if (*strs == NULL)
		return (1);
	ft_strlcpy(*strs, start, (s - start + 1));
	return (0);
}
