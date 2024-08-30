/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:32:01 by damin             #+#    #+#             */
/*   Updated: 2023/10/29 18:34:25 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*flist;
	t_list	*iterl;
	void	*data;

	if (!lst || !f)
		return (NULL);
	flist = NULL;
	while (lst)
	{
		data = f(lst->content);
		iterl = ft_lstnew(data);
		if (!iterl)
		{
			del(data);
			ft_lstclear(&flist, del);
			return (NULL);
		}
		ft_lstadd_back(&flist, iterl);
		lst = lst->next;
	}
	return (flist);
}
