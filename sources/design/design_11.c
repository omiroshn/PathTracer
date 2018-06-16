/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_11.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 20:08:29 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/29 14:00:10 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ctrl_tabs_click(t_env *env, t_control *c)
{
	if (env->active_tab == *(t_tab *)c->tag)
		env->active_tab = NO_TAB;
	else
		env->active_tab = *(t_tab *)c->tag;
	init_controls(env);
}

void	init_screenshot_button(t_env *env)
{
	static t_control	*s_s = NULL;

	if (!s_s)
	{
		if (!(s_s = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		s_s->name = "s_s_btn";
		s_s->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	s_s->font_size = 12;
	s_s->anchor = &sgl_find_control(env->win, "actions_p")->align;
	s_s->align = (SDL_Rect){101, 4, 65, 16};
	s_s->click_callback = screenshot;
	s_s->callback_data = env;
	ft_strcpy(s_s->text, "Screenshot");
}

void	init_save_scene_button(t_env *env)
{
	static t_control	*s_c = NULL;

	if (!s_c)
	{
		if (!(s_c = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		s_c->name = "save_scene_btn";
		s_c->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	s_c->font_size = 12;
	s_c->anchor = &sgl_find_control(env->win, "actions_p")->align;
	s_c->align = (SDL_Rect){167, 4, 40, 16};
	s_c->click_callback = save_scene;
	s_c->callback_data = env;
	ft_strcpy(s_c->text, "Export");
}
