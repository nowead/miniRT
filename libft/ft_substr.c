/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:09:33 by damin             #+#    #+#             */
/*   Updated: 2023/10/30 15:13:46 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	i;
	size_t			s_len;

	s_len = ft_strlen(s);
	if (s_len > start && start + len >= s_len)
		tmp = (char *)malloc((s_len - start + 1) * sizeof(char));
	else if (s_len > start && start + len < s_len)
		tmp = (char *)malloc((len + 1) * sizeof(char));
	else
		tmp = (char *)malloc(sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len && s_len > start)
	{
		tmp[i] = s[start];
		++start;
		++i;
		if (s[start] == '\0')
			break ;
	}
	tmp[i] = '\0';
	return (tmp);
}
