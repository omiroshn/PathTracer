/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:24:16 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/09 17:51:35 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **dlst)
{
	t_dlist	*node;
	t_dlist	*tmp;

	if (!dlst || !*dlst)
		return ;
	node = *dlst;
	tmp = node->next;
	while ((node = tmp) != *dlst)
	{
		tmp = node->next;
		ft_dlstdelelem(&node);
	}
	ft_memdel((void **)dlst);
}
