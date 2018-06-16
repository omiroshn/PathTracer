/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:05:11 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/29 21:25:07 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memjoin(const void *m1, const void *m2, size_t b1, size_t b2)
{
	void	*new;

	if (!m1 && !m2)
		return (NULL);
	if (!(new = (void *)malloc((b1 + b2))))
		return (NULL);
	ft_memcpy(new, m1, b1);
	ft_memcpy(new + b1, m2, b2);
	return (new);
}
