/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_atop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:26:39 by pgritsen          #+#    #+#             */
/*   Updated: 2018/03/06 17:44:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

static inline void	free_splited(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static inline int	count_splited(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

t_point				sgl_atop(const char *src)
{
	t_point	ret;
	char	*tmp;
	char	**arr;

	if (!(tmp = ft_get_content(src, '{', '}')))
		return ((t_point){INFINITY, INFINITY, INFINITY});
	if (count_splited((arr = ft_strsplit(tmp, ';'))) != 3)
		return ((t_point){INFINITY, INFINITY, INFINITY});
	ft_memdel((void **)&tmp);
	ret.x = ft_atof(arr[0]);
	ret.y = ft_atof(arr[1]);
	ret.z = ft_atof(arr[2]);
	free_splited(arr);
	return (ret);
}
