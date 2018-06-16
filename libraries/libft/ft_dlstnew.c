/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 20:00:28 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/19 16:21:49 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist		*ft_dlstnew(void *content, size_t content_size)
{
	t_dlist	*new;

	if (!(new = malloc(sizeof(t_dlist))))
		return (NULL);
	new->prev = new;
	new->next = new;
	new->content = content;
	new->content_size = content ? content_size : 0;
	return (new);
}
