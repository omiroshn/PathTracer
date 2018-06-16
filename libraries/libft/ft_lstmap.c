/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:14:17 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:57:29 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	s_clean(void *content, size_t content_size)
{
	if (!content)
		return ;
	ft_bzero(content, content_size);
	free(content);
}

static void	node_del(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	ft_memdel(&content);
	content_size = 0;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;
	t_list	*new;
	t_list	*buff;

	new = NULL;
	result = NULL;
	while (lst && f)
	{
		if (!(buff = ft_lstnew(lst->content, lst->content_size))
			|| !(new = f(buff)))
		{
			ft_lstdel(&result, s_clean);
			return (NULL);
		}
		if (new != buff)
			ft_lstdel(&buff, &node_del);
		ft_lstadd_back(&result, new);
		new = result->next;
		lst = lst->next;
	}
	return (result);
}
