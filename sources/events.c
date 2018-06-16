/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:01:53 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/08 11:57:16 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	key_down_handler(SDL_Scancode key, t_env *env)
{
	t_uchar	e;

	e = 0;
	!env->flags.pause && key == SDL_SCANCODE_M ? env->flags.move_m ^= 0b1 : 0;
	SDL_SetRelativeMouseMode(env->flags.move_m);
	env->flags.move_m ? movement_keys(key, env, 1) : 0;
	e ? init_scene(env) : 0;
}

static void	key_up_handler(SDL_Scancode key, t_env *env)
{
	t_uchar	e;

	e = 0;
	env->flags.move_m ? movement_keys(key, env, 0) : 0;
	e ? init_scene(env) : 0;
}

static void	mouse_move_handler(t_env *env)
{
	int					x;
	int					y;
	static SDL_Cursor	*def = 0;

	!def ? def = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) : 0;
	!def ? ft_err_handler("Cursor didn't loaded", 0, 0, 1) : SDL_SetCursor(def);
	SDL_GetMouseState(&x, &y);
	env->flags.move_m ? view_mousemove(env) : 0;
	env->flags.obj_info ? obj_info_mouse_move_handler(x, y, env) : 0;
}

static void	mouse_click_handler(t_env *e, SDL_Event *event)
{
	uint	ex;
	int		x;
	int		y;

	if (event->button.state == SDL_RELEASED && !(e->sel_obj.drag = 0))
		return ;
	ex = 0;
	SDL_GetMouseState(&x, &y);
	ex |= !ex && e->flags.obj_info ? obj_info_mouse_click_handler(x, y, e) : 0;
	ex |= !ex ? stats_handler(x, y) : 0;
	ex |= !ex && !e->flags.move_m ? find_obj(e) : 0;
}

int			poll_events(t_env *env)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE
			|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == EXIT_KEY))
			return (0);
		else if (e.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			sgl_win_resize(e.window.windowID, e.window.data1, e.window.data2);
			resize_viewport(env->cam->vwp, e.window.data1, e.window.data2);
			env->load_progress >= 1.0F ? init_scene(env) : 0;
		}
		else if (env->load_progress < 1.0F || sgl_handle_controls(&e))
			continue ;
		else if (e.type == SDL_KEYDOWN)
			key_down_handler(e.key.keysym.scancode, env);
		else if (e.type == SDL_KEYUP)
			key_up_handler(e.key.keysym.scancode, env);
		else if (e.type == SDL_MOUSEMOTION)
			mouse_move_handler(env);
		else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			mouse_click_handler(env, &e);
	return (1);
}
