/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:51:50 by damin             #+#    #+#             */
/*   Updated: 2023/10/26 17:46:25 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*lstptr;

	if (!lst || !new)
		return ;
	lstptr = new;
	lstptr = ft_lstlast(lstptr);
	lstptr->next = *lst;
	*lst = new;
}
