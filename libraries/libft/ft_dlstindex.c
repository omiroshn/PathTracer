/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 20:26:29 by grevenko          #+#    #+#             */
/*   Updated: 2018/06/07 20:44:23 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstindex(t_dlist *lst, size_t index)
{
	t_dlist	*ret;

	ret = lst;
	while (ret && (ret = ret->next) != lst && index--)
		;
	return (index && ret != lst ? ret : 0);
}
