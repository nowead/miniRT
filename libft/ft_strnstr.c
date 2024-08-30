/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:11:28 by damin             #+#    #+#             */
/*   Updated: 2023/10/25 18:52:10 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hi;
	size_t	ni;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	hi = 0;
	while (haystack[hi] && hi < len)
	{
		ni = 0;
		while (needle[ni] && haystack[hi + ni] == needle[ni] && hi + ni < len)
			++ni;
		if (ni == needle_len)
			return ((char *)&haystack[hi]);
		++hi;
	}
	return (NULL);
}
