/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_push_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:11:54 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/10 20:57:29 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ftstring.h"

static t_string	*set_new_node(char symb)
{
	t_string	*new_node;

	if (!(new_node = (t_string *)ft_memalloc(sizeof(t_string))))
		return (NULL);
	new_node->prev = NULL;
	new_node->symb = symb;
	new_node->next = NULL;
	return (new_node);
}

t_string		*ft_string_push_back(t_string **dst, const char *s)
{
	t_string	*ptr;
	t_string	*new_node;

	if (!dst)
		return (NULL);
	else if (!s)
		return (*dst);
	ptr = *dst;
	while (*dst && (*dst)->next)
		dst = &(*dst)->next;
	while ((new_node = set_new_node(*s++))->symb)
	{
		if (!*dst)
			*dst = new_node;
		else
		{
			new_node->prev = *dst;
			(*dst)->next = new_node;
			dst = &(*dst)->next;
		}
	}
	return (ptr);
}
