/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:23:18 by damin             #+#    #+#             */
/*   Updated: 2023/10/26 18:25:47 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lstptr;

	if (!lst || !f)
		return ;
	lstptr = lst;
	while (lstptr)
	{
		f(lstptr->content);
		lstptr = lstptr->next;
	}
}
