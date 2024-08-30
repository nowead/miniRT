/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:12:43 by damin             #+#    #+#             */
/*   Updated: 2023/10/25 16:38:01 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	tmp = (char *)malloc((s1_len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tmp[i] = ((char *)s1)[i];
		++i;
	}
	tmp[i] = '\0';
	return (tmp);
}
