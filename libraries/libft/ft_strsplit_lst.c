/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 21:27:45 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/13 15:42:37 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		node_del(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	ft_memdel(&content);
	content_size = 0;
}

t_list			*ft_strsplit_lst(char const *s, char c)
{
	t_list	*list;
	t_list	*tmp;
	char	*p_s;
	size_t	w_l;

	list = NULL;
	if (!s)
		return (NULL);
	if (!*(p_s = ft_strntrim(s, c)))
		return (NULL);
	while (*p_s)
	{
		p_s = ft_strntrim(p_s, c);
		w_l = ft_strclen(p_s, c);
		if (!(tmp = ft_lstnew((void *)ft_strsub(p_s, 0, w_l), w_l + 1)))
		{
			ft_lstdel(&list, &node_del);
			return (NULL);
		}
		ft_lstadd_back(&list, tmp);
		p_s += w_l;
	}
	return (list);
}
