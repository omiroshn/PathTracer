/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 20:11:36 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/08 21:01:48 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstpush(t_dlist **dest, t_dlist *src)
{
	if (!dest || !src)
		return ;
	!*dest ? *dest = ft_dlstnew(NULL, 0) : 0;
	(*dest)->next->prev = src;
	src->next = (*dest)->next;
	src->prev = *dest;
	(*dest)->next = src;
}
