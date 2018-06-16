/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 20:58:45 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/08 21:03:27 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dlstsize(t_dlist *dlst)
{
	t_dlist	*tmp;
	size_t	size;

	if (!dlst)
		return (0);
	size = 0;
	tmp = dlst;
	while ((tmp = tmp->next) != dlst)
		size++;
	return (size);
}
