/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:54:47 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/04 17:39:01 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;
	t_list	*buff;

	if (!alst || !del)
		return ;
	lst = *alst;
	while (lst)
	{
		del(lst->content, lst->content_size);
		buff = lst->next;
		ft_memdel((void **)&lst);
		lst = buff;
	}
	*alst = NULL;
}
