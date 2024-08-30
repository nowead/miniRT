/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:07:21 by damin             #+#    #+#             */
/*   Updated: 2023/10/26 14:43:06 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*handle_excep(void)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*tmp;
	size_t		front;
	size_t		rear;

	front = 0;
	rear = ft_strlen(s1);
	if (!s1)
	{
		tmp = handle_excep();
		return (tmp);
	}
	while (s1[front] && ft_strchr(set, s1[front]))
		++front;
	while (rear >= 1 && ft_strchr(set, s1[rear - 1]))
		--rear;
	if (front >= rear)
	{
		tmp = handle_excep();
		return (tmp);
	}
	tmp = (char *)malloc((rear - front + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, s1 + front, rear - front + 1);
	return (tmp);
}
