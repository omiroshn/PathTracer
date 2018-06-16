/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:23:18 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:58:59 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char		*tmp;
	size_t		it;

	tmp = (char *)malloc((size + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	it = 0;
	while (it <= size)
		tmp[it++] = 0;
	return (tmp);
}
