/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpush_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 20:51:23 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/08 20:53:12 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstpush_back(t_dlist **dest, t_dlist *src)
{
	if (!dest || !src)
		return ;
	!*dest ? *dest = ft_dlstnew(NULL, 0) : 0;
	src->prev = (*dest)->prev;
	src->next = *dest;
	(*dest)->prev->next = src;
	(*dest)->prev = src;
}
