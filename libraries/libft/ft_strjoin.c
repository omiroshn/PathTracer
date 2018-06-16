/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:59:27 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/06 14:31:59 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	s1_l;
	size_t	s2_l;

	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		s1 = "";
	s1_l = ft_strlen(s1);
	if (!s2)
		s2 = "";
	s2_l = ft_strlen(s2);
	if (!(new = (char *)malloc((s1_l + s2_l + 1) * sizeof(char))))
		return (NULL);
	*new = 0;
	ft_strlcat(new, s1, s1_l + s2_l + 1);
	ft_strlcat(new, s2, s1_l + s2_l + 1);
	return (new);
}
