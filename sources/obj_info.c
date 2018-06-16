/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:41:18 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/05 19:11:51 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	draw_info_fields(SDL_Rect *p, t_font f[2],
									char *buf, t_env *env)
{
	SDL_Renderer	*rend;
	SDL_Rect		b_size;

	rend = env->win->rend;
	b_size = sgl_str_size(&f[1], buf);
	sgl_draw_str(buf, &f[1],
		(t_point){p->x + (p->w - b_size.w) / 2, p->y + 5, 0}, rend);
	sgl_draw_str("Color: #", f, (t_point){p->x + 8, p->y + 40, 0}, rend);
	sgl_draw_str("Position", &f[1], (t_point){p->x + 28, p->y + 62, 0}, rend);
	sgl_draw_str("X:", f, (t_point){p->x + 8, p->y + 80, 0}, rend);
	sgl_draw_str("Y:", f, (t_point){p->x + 8, p->y + 95, 0}, rend);
	sgl_draw_str("Z:", f, (t_point){p->x + 8, p->y + 110, 0}, rend);
	sgl_draw_str("Emission: ", f, (t_point){p->x + 8, p->y + 130, 0}, rend);
	sgl_draw_str("P1: ", f, (t_point){p->x + 8, p->y + 150, 0}, rend);
	sgl_draw_str("P2: ", f, (t_point){p->x + 95, p->y + 150, 0}, rend);
	sgl_draw_str_center("Material", &f[1],
		(SDL_Rect){p->x, p->y + 170, p->w, 0}, rend);
	sgl_draw_str_center("Specularity", &f[1],
		(SDL_Rect){p->x + 2, p->y + 210, p->w, 0}, rend);
	sgl_draw_str_center("Tiling", &f[1],
		(SDL_Rect){p->x, p->y + 255, p->w, 0}, rend);
}

void				draw_info(SDL_Rect *p, t_env *env)
{
	static SDL_Texture	*c_img = NULL;
	static char			buf[64];
	t_font				bf;
	t_font				hf;

	bf = (t_font){"SourceSans", 16, 0xFFFFFF, 0};
	hf = (t_font){"SourceSans", 16, 0x9b0d0d, 0};
	!c_img ? c_img = sgl_surftotex(env->win->rend,
								sgl_imgload(IMAGES_FOLDER"close.png"), 1) : 0;
	!c_img ? ft_err_handler(IMAGES_FOLDER"close.png", "Not Found!", 0, 1) : 0;
	*p = (SDL_Rect){p->x, p->y, 200, 300};
	p->x + p->w / 2 >= env->win->w ? p->x = env->win->w - p->w / 2 : 0;
	p->y + p->h / 2 >= env->win->h ? p->y = env->win->h - p->h / 2 : 0;
	SDL_SetRenderDrawColor(env->win->rend, 0xC0, 0xC0, 0xC0, 0xFF);
	SDL_RenderFillRect(env->win->rend, p);
	SDL_SetRenderDrawColor(env->win->rend, 0xAA, 0xAA, 0xAA, 0xFF);
	SDL_RenderFillRect(env->win->rend,
		&(SDL_Rect){p->x + 3, p->y + 3, p->w - 6, p->h - 6});
	SDL_RenderCopy(env->win->rend, c_img, 0,
		&(SDL_Rect){p->x - 8, p->y - 8, 20, 20});
	sprintf(buf, "#%d %s", env->sel_obj.obj.id,
		*get_obj_type(env->sel_obj.obj.type, 1, 0));
	draw_info_fields(p, (t_font[2]){bf, hf}, buf, env);
}

uint				obj_info_mouse_click_handler(int x, int y, t_env *e)
{
	uint	ret;

	ret = 0;
	if (sqrt(pow(x - e->sel_obj.pos.x, 2) + pow(y - e->sel_obj.pos.y, 2)) < 10
		&& ++ret)
	{
		e->flags.obj_info = 0;
		init_controls(e);
	}
	else if (x >= e->sel_obj.pos.x && x <= e->sel_obj.pos.x + e->sel_obj.pos.w
		&& y >= e->sel_obj.pos.y && y <= e->sel_obj.pos.y + 10 && ++ret)
	{
		SDL_GetMouseState(&e->sel_obj.drag, NULL);
		e->sel_obj.drag -= e->sel_obj.pos.x;
	}
	else if (x >= e->sel_obj.pos.x && x <= e->sel_obj.pos.x + e->sel_obj.pos.w
		&& y >= e->sel_obj.pos.y && y <= e->sel_obj.pos.y + e->sel_obj.pos.h)
		ret++;
	return (ret);
}

void				obj_info_mouse_move_handler(int x, int y, t_env *e)
{
	static SDL_Cursor	*pointer = 0;
	static SDL_Cursor	*move = 0;

	!pointer ? pointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND) : 0;
	!move ? move = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL) : 0;
	if (sqrt(pow(x - e->sel_obj.pos.x, 2) + pow(y - e->sel_obj.pos.y, 2)) < 10)
		!pointer ? ERR("Cursor didn't loaded") : SDL_SetCursor(pointer);
	else if (x >= e->sel_obj.pos.x && x <= e->sel_obj.pos.x + e->sel_obj.pos.w
		&& y >= e->sel_obj.pos.y && y <= e->sel_obj.pos.y + 10)
		!move ? ERR("Cursor didn't loaded") : SDL_SetCursor(move);
	e->sel_obj.drag ? (e->sel_obj.pos.x = x)
					&& (e->sel_obj.pos.y = y) : 0;
	e->sel_obj.drag ? e->sel_obj.pos.x -= e->sel_obj.drag : 0;
}

uint				find_obj(t_env *env)
{
	SDL_Rect	tmp;
	cl_int		err;
	cl_kernel	kl;
	cl_float3	dir;

	tmp.w = 1;
	SDL_GetMouseState(&tmp.x, &tmp.y);
	tmp.x -= env->cam->vwp->wd_width / 2;
	tmp.y = env->cam->vwp->wd_height / 2 - tmp.y;
	dir = dir_vector((t_point){tmp.x * env->cam->vwp->vw_width /
			env->cam->vwp->wd_width, tmp.y * env->cam->vwp->vw_height /
			env->cam->vwp->wd_height, tmp.w}, env);
	err = 0;
	kl = env->sel_obj.kl.kernel;
	err |= clSetKernelArg(kl, 0, sizeof(cl_mem), &env->sel_obj.kl.mem);
	err |= clSetKernelArg(kl, 1, sizeof(cl_mem), &env->scene.objs);
	err |= clSetKernelArg(kl, 2, sizeof(cl_float3), &env->cam->pos);
	err |= clSetKernelArg(kl, 3, sizeof(cl_float3), &dir);
	err |= clEnqueueTask(env->cl.queue, kl, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(env->cl.queue, env->sel_obj.kl.mem, CL_TRUE, 0,
								sizeof(t_obj), &env->sel_obj.obj, 0, 0, 0);
	err ? ft_err_handler("OpenCL", "Fail!", 0, 1) : 0;
	env->flags.obj_info = env->sel_obj.obj.type != -1;
	init_controls(env);
	return (env->flags.obj_info);
}
