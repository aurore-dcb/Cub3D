/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:28:41 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/02 11:28:46 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_elem;
	t_list	*n_list;

	n_list = NULL;
	n_elem = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			n_elem = ft_lstnew((*f)(lst->content));
			if (!n_elem)
			{
				ft_lstclear(&n_list, del);
				return (NULL);
			}
			ft_lstadd_back(&n_list, n_elem);
			lst = lst->next;
		}
		return (n_list);
	}
	return (NULL);
}
