/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 19:34:16 by pgritsen          #+#    #+#             */
/*   Updated: 2018/03/05 19:55:33 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_content(const char *src, char open, char close)
{
	char	*start_p;
	char	*end_p;
	char	*ret;

	if (!(start_p = ft_strchr(src, open)))
		return (NULL);
	if (!(end_p = ft_strchr(start_p + 1, close)))
		return (NULL);
	if (!(ret = ft_strsub(start_p, 1, end_p - start_p - 1)))
		return (NULL);
	return (ret);
}
