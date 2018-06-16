/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_12.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 20:51:09 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 14:23:01 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_effects_tab_button(t_env *env)
{
	static t_control	*effects_t = NULL;
	static t_tab		f_n = EFFECTS;

	if (!effects_t)
	{
		if (!(effects_t = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		effects_t->name = "effects_t";
		effects_t->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	effects_t->font_size = 12;
	effects_t->anchor = &sgl_find_control(env->win, "actions_p")->align;
	effects_t->align = (SDL_Rect){55, 4, 45, 16};
	effects_t->click_callback = ctrl_tabs_click;
	effects_t->callback_data = env;
	ft_strcpy(effects_t->text, "Effects");
	ft_memcpy(effects_t->tag, &f_n, sizeof(t_tab));
}

void	init_bnw_effect_button(t_env *env)
{
	static t_control	*bnw_e_btn = NULL;
	static t_effect		f_n = BLACK_N_WHITE;

	if (!bnw_e_btn)
	{
		if (!(bnw_e_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		bnw_e_btn->name = "bnw_e_btn";
		bnw_e_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	bnw_e_btn->visible = env->active_tab == EFFECTS;
	bnw_e_btn->font_size = 12;
	bnw_e_btn->anchor = &sgl_find_control(env->win, "effects_p")->align;
	bnw_e_btn->align = (SDL_Rect){195, 4, 70, 16};
	bnw_e_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->flags.effect == f_n)
		bnw_e_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	bnw_e_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	bnw_e_btn->fore_color = 0x323335;
	env->flags.effect == f_n ? bnw_e_btn->fore_color = 0x990000 : 0;
	bnw_e_btn->click_callback = ctrl_effect_click;
	bnw_e_btn->callback_data = env;
	ft_strcpy(bnw_e_btn->text, "Black&White");
	ft_memcpy(bnw_e_btn->tag, &f_n, sizeof(t_effect));
}

void	init_casting_effect_button(t_env *env)
{
	static t_control	*casting_e_btn = NULL;
	static t_effect		f_n = CASTING;

	if (!casting_e_btn)
	{
		if (!(casting_e_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		casting_e_btn->name = "casting_e_btn";
		casting_e_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	casting_e_btn->visible = env->active_tab == EFFECTS;
	casting_e_btn->font_size = 12;
	casting_e_btn->anchor = &sgl_find_control(env->win, "effects_p")->align;
	casting_e_btn->align = (SDL_Rect){266, 4, 50, 16};
	casting_e_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->flags.effect == f_n)
		casting_e_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	casting_e_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	casting_e_btn->fore_color = 0x323335;
	env->flags.effect == f_n ? casting_e_btn->fore_color = 0x990000 : 0;
	casting_e_btn->click_callback = ctrl_effect_click;
	casting_e_btn->callback_data = env;
	ft_strcpy(casting_e_btn->text, "Casting");
	ft_memcpy(casting_e_btn->tag, &f_n, sizeof(t_effect));
}

void	init_fxaa_effect_button(t_env *env)
{
	static t_control	*fxaa_e_btn = NULL;
	static t_effect		f_n = ANTIALIASING;

	if (!fxaa_e_btn)
	{
		if (!(fxaa_e_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		fxaa_e_btn->name = "fxaa_e_btn";
		fxaa_e_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	fxaa_e_btn->visible = env->active_tab == EFFECTS;
	fxaa_e_btn->font_size = 12;
	fxaa_e_btn->anchor = &sgl_find_control(env->win, "effects_p")->align;
	fxaa_e_btn->align = (SDL_Rect){317, 4, 30, 16};
	fxaa_e_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->flags.effect == f_n)
		fxaa_e_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	fxaa_e_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	fxaa_e_btn->fore_color = 0x323335;
	env->flags.effect == f_n ? fxaa_e_btn->fore_color = 0x990000 : 0;
	fxaa_e_btn->click_callback = ctrl_effect_click;
	fxaa_e_btn->callback_data = env;
	ft_strcpy(fxaa_e_btn->text, "AA");
	ft_memcpy(fxaa_e_btn->tag, &f_n, sizeof(t_effect));
}

void	init_oil_effect_button(t_env *env)
{
	static t_control	*oil_e_btn = NULL;
	static t_effect		f_n = OIL;

	if (!oil_e_btn)
	{
		if (!(oil_e_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		oil_e_btn->name = "oil_e_btn";
		oil_e_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	oil_e_btn->visible = env->active_tab == EFFECTS;
	oil_e_btn->font_size = 12;
	oil_e_btn->anchor = &sgl_find_control(env->win, "effects_p")->align;
	oil_e_btn->align = (SDL_Rect){350, 4, 70, 16};
	oil_e_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->flags.effect == f_n)
		oil_e_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	oil_e_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	oil_e_btn->fore_color = 0x323335;
	env->flags.effect == f_n ? oil_e_btn->fore_color = 0x990000 : 0;
	oil_e_btn->click_callback = ctrl_effect_click;
	oil_e_btn->callback_data = env;
	ft_strcpy(oil_e_btn->text, "OIL Painting");
	ft_memcpy(oil_e_btn->tag, &f_n, sizeof(t_effect));
}
