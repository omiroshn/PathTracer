/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_rotate_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:38:42 by pgritsen          #+#    #+#             */
/*   Updated: 2018/03/06 17:46:00 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_point		sgl_rotate_point(t_point p, t_rotate angle)
{
	t_point	sin_c;
	t_point	cos_c;
	t_point	rx;
	t_point	ry;
	t_point	rz;

	sin_c.x = sin(angle.rx * M_PI / 180.0);
	cos_c.x = cos(angle.rx * M_PI / 180.0);
	sin_c.y = sin(angle.ry * M_PI / 180.0);
	cos_c.y = cos(angle.ry * M_PI / 180.0);
	sin_c.z = sin(angle.rz * M_PI / 180.0);
	cos_c.z = cos(angle.rz * M_PI / 180.0);
	rx.x = p.x;
	rx.y = p.y * cos_c.x + p.z * sin_c.x;
	rx.z = p.z * cos_c.x - p.y * sin_c.x;
	ry.x = rx.x * cos_c.y - rx.z * sin_c.y;
	ry.y = rx.y;
	ry.z = rx.z * cos_c.y + rx.x * sin_c.y;
	rz.x = ry.x * cos_c.z + ry.y * sin_c.z;
	rz.y = ry.y * cos_c.z - ry.x * sin_c.z;
	rz.z = ry.z;
	return (rz);
}
