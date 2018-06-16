/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:38:44 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/10 20:57:20 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *s1, char const *s2)
{
	if (!s1 && s2)
		return ((unsigned char)*s2);
	else if (!s2 && s1)
		return ((unsigned char)*s1);
	else if (!s1 && !s2)
		return (0);
	while ((*s1 || *s2))
		if ((unsigned char)*s1++ != (unsigned char)*s2++)
			return (0);
	return (1);
}
