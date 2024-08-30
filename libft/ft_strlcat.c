/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:34:58 by damin             #+#    #+#             */
/*   Updated: 2023/10/16 14:12:23 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (dst_len > dstsize)
		return (src_len + dstsize);
	else
	{
		while (i + dst_len < dstsize)
		{
			dst[i + dst_len] = src[i];
			if (!src[i])
				break ;
			if (i + dst_len + 1 == dstsize)
				dst[i + dst_len] = 0;
			++i;
		}
		return (dst_len + src_len);
	}
}
