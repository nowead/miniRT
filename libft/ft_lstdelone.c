/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:42:11 by damin             #+#    #+#             */
/*   Updated: 2023/10/26 18:13:16 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*lstptr;

	if (!lst && !del)
		return ;
	if (lst->next == NULL)
	{
		del(lst->content);
		free(lst);
	}
	else
	{
		del(lst->content);
		lstptr = lst;
		lst = lst->next;
		free(lstptr);
	}
}
