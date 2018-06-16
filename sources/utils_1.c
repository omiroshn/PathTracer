/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:16:00 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 12:09:57 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	tofloat3(t_point point)
{
	cl_float3	tmp;

	tmp.x = (float)point.x;
	tmp.y = (float)point.y;
	tmp.z = (float)point.z;
	return (tmp);
}

t_point		topoint(cl_float3 point)
{
	t_point	tmp;

	tmp.x = point.x;
	tmp.y = point.y;
	tmp.z = point.z;
	return (tmp);
}

inline void	display_usage(t_uchar help)
{
	ft_printf("Usage: {green}./RT{nc} [{cyan}scene file | -help{nc}]\n");
	!help ? exit(0) : 0;
	ft_printf("{cyan}Scene file format:{nc}\n"
"    It's simple JSON format, you can set up {green}camera, ambient_light,\n"
"  figures and external .obj files.{nc}\n{cyan}Map example:{nc}\n"
"{\n"
"  \"camera\": {\n"
"    \"position\": [0, 0.5, -4],\n"
"    \"angles\": [0, 0, 0]\n"
"  },\n"
"  \"ambient_light\" : 0.1,\n"
"  \"figures\": [\n"
"    {\n"
"      \"type\": \"sphere\",\n"
"      \"center\": [0, 0, 0],\n"
"      \"radius\": 1\n"
"      \"color\": [0.9, 0.67, 0.44],\n"
"      \"material\": \"diffuse\"\n"
"    }\n"
"  ]\n"
"}\n");
	exit(0);
}

void		resize_viewport(t_viewport *vwp, int width, int height)
{
	if (width > height)
	{
		vwp->vw_height = 1.0;
		vwp->vw_width = (double)width / height;
	}
	else
	{
		vwp->vw_width = 1.0;
		vwp->vw_height = (double)height / width;
	}
	vwp->wd_width = width;
	vwp->wd_height = height;
}

void		init_env(t_env *env)
{
	srand(time(NULL));
	ft_bzero(env, sizeof(t_env));
	env->win = sgl_new_window(PROGRAM_NAME, W_WIDTH, W_HEIGHT,
								SDL_WINDOW_RESIZABLE);
	env->cam = ft_memalloc(sizeof(t_cam));
	env->cam->vwp = ft_memalloc(sizeof(t_viewport));
	resize_viewport(env->cam->vwp, env->win->w, env->win->h);
	env->cam->vwp->dist = 1;
	env->sel_obj.pos = (SDL_Rect){25, 60, 0, 0};
	env->sel_obj.obj.type = -1;
	env->move_speed = 0.008F;
	cl_init(&env->cl, CL_DEVICE_TYPE_GPU);
}
