/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_check_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:54:06 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/12 14:08:46 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

int		sgl_check_point(t_point src)
{
	if (src.x != src.x || src.x == INFINITY
		|| src.y != src.y || src.y == INFINITY
		|| src.z != src.z || src.z == INFINITY)
		return (0);
	return (1);
}
