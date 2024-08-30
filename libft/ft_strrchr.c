/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:57:08 by damin             #+#    #+#             */
/*   Updated: 2023/10/29 19:58:37 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*tmp;

	i = (int)ft_strlen(s);
	tmp = (char *)s;
	while (i >= 0)
	{
		if (tmp[i] == (char)c)
			return (tmp + i);
		--i;
	}
	return (NULL);
}
