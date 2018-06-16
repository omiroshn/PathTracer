/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:32:50 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/12 21:18:36 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		apply_effect(t_env *env)
{
	t_effect	effect;
	cl_int		err;
	cl_kernel	kl;

	err = 0;
	kl = env->vis_effect.kernel;
	effect = env->flags.effect;
	err |= clEnqueueWriteBuffer(env->cl.queue, env->vis_effect.mem, CL_TRUE,
		0, sizeof(uint) * env->win->w * env->win->h,
		env->win->surf->pixels, 0, 0, 0);
	err |= clSetKernelArg(kl, 0, sizeof(cl_mem), &env->vis_effect.mem);
	err |= clSetKernelArg(kl, 1, sizeof(t_effect), &effect);
	err |= clSetKernelArg(kl, 2, sizeof(cl_mem), &env->vis_effect.mem_out);
	err |= clEnqueueNDRangeKernel(env->cl.queue, kl, 2, NULL,
		(size_t[3]){env->win->w, env->win->h, 0}, NULL, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(env->cl.queue, env->vis_effect.mem_out, CL_TRUE,
		0, sizeof(uint) * env->win->w * env->win->h, env->win->surf->pixels,
		0, 0, 0);
	err ? ft_err_handler("OpenCL", "Fail!", 0, 1) : 0;
}

void		init_scene(t_env *e)
{
	cl_int		err;
	cl_kernel	kl;

	e->scene.sampls = 0;
	e->scene.timestamp = SDL_GetTicks();
	err = 0;
	kl = e->cam->kl.kernel;
	cl_reinit_mem(&e->cl, &e->vis_effect.mem, 4 * e->win->w * e->win->h, 0);
	cl_reinit_mem(&e->cl, &e->vis_effect.mem_out, 4 * e->win->w * e->win->h, 0);
	cl_reinit_mem(&e->cl, &e->cam->kl.mem, F3_S * e->win->w * e->win->h, 0);
	clEnqueueFillBuffer(e->cl.queue, e->cam->kl.mem, &err, sizeof(cl_int),
		0, sizeof(cl_float3) * e->win->w * e->win->h, 0, 0, 0);
	err |= clSetKernelArg(kl, 0, sizeof(cl_mem), &e->cam->kl.mem);
	err |= clSetKernelArg(kl, 1, sizeof(cl_float3), &e->cam->pos);
	err |= clSetKernelArg(kl, 2, sizeof(cl_float3), &e->cam->rot);
	err |= clSetKernelArg(kl, 3, sizeof(t_viewport), e->cam->vwp);
	cl_reinit_mem(&e->cl, &e->scene.objs,
		sizeof(t_obj) * (e->scene.objs_c + 1), e->scene.objs_h);
	err |= clSetKernelArg(kl, 4, sizeof(cl_mem), &e->scene.objs);
	err |= clSetKernelArg(kl, 7, sizeof(float), &e->scene.ambient_light);
	err |= clSetKernelArg(kl, 8, sizeof(cl_mem), &e->vis_effect.mem);
	err |= clSetKernelArg(kl, 9, sizeof(cl_mem), &e->scene.texs);
	err |= clSetKernelArg(kl, 10, sizeof(cl_mem), &e->scene.texs_info);
	err |= clSetKernelArg(kl, 11, sizeof(cl_mem), &e->scene.texs_vt);
	err ? ft_err_handler("OpenCL", "Fail!", 0, 1) : 0;
}

void		render_scene(t_env *env)
{
	cl_kernel	kl;
	uint		random_seed;
	char		smooth;
	cl_int		err;
	int			it;

	kl = env->cam->kl.kernel;
	env->scene.sampls++;
	err = 0;
	it = -1;
	smooth = 1 + (env->flags.effect == ANTIALIASING) * 2;
	random_seed = rand();
	err |= clSetKernelArg(kl, 5, sizeof(uint), &random_seed);
	err |= clSetKernelArg(kl, 6, sizeof(uint), &env->scene.sampls);
	err |= clSetKernelArg(kl, 12, sizeof(char), &smooth);
	err |= clEnqueueNDRangeKernel(env->cl.queue, kl, 2, NULL,
		(size_t[3]){env->win->w, env->win->h, 0}, NULL, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(env->cl.queue, env->vis_effect.mem, CL_TRUE,
		0, 4 * env->win->w * env->win->h,
		env->win->surf->pixels, 0, 0, 0);
	err ? ft_err_handler("OpenCL", "Fail!", 0, 1) : 0;
}
