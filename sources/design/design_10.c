/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_10.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 19:52:47 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 17:02:45 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ctrl_effect_click(t_env *env, t_control *c)
{
	if (env->flags.effect == *(t_effect *)c->tag)
		env->flags.effect = NO_EFFECT;
	else
		env->flags.effect = *(t_effect *)c->tag;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	if (ANTIALIASING == *(t_effect *)c->tag)
		init_scene(env);
	init_controls(env);
}

void	init_negative_effect_button(t_env *env)
{
	static t_control	*negative_e_btn = NULL;
	static t_effect		f_n = NEGATIVE;

	if (!negative_e_btn)
	{
		if (!(negative_e_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		negative_e_btn->name = "negative_e_btn";
		negative_e_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	negative_e_btn->visible = env->active_tab == EFFECTS;
	negative_e_btn->font_size = 12;
	negative_e_btn->anchor = &sgl_find_control(env->win, "effects_p")->align;
	negative_e_btn->align = (SDL_Rect){4, 4, 50, 16};
	negative_e_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->flags.effect == f_n)
		negative_e_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	negative_e_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	negative_e_btn->fore_color = 0x323335;
	env->flags.effect == f_n ? negative_e_btn->fore_color = 0x990000 : 0;
	negative_e_btn->click_callback = ctrl_effect_click;
	negative_e_btn->callback_data = env;
	ft_strcpy(negative_e_btn->text, "Negative");
	ft_memcpy(negative_e_btn->tag, &f_n, sizeof(t_effect));
}

void	init_sepia_effect_button(t_env *env)
{
	static t_control	*sepia_e_btn = NULL;
	static t_effect		f_n = SEPIA;

	if (!sepia_e_btn)
	{
		if (!(sepia_e_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		sepia_e_btn->name = "sepia_e_btn";
		sepia_e_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	sepia_e_btn->visible = env->active_tab == EFFECTS;
	sepia_e_btn->font_size = 12;
	sepia_e_btn->anchor = &sgl_find_control(env->win, "effects_p")->align;
	sepia_e_btn->align = (SDL_Rect){57, 4, 35, 16};
	sepia_e_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->flags.effect == f_n)
		sepia_e_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	sepia_e_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	sepia_e_btn->fore_color = 0x323335;
	env->flags.effect == f_n ? sepia_e_btn->fore_color = 0x990000 : 0;
	sepia_e_btn->click_callback = ctrl_effect_click;
	sepia_e_btn->callback_data = env;
	ft_strcpy(sepia_e_btn->text, "Sepia");
	ft_memcpy(sepia_e_btn->tag, &f_n, sizeof(t_effect));
}

void	init_grayscale_effect_button(t_env *env)
{
	static t_control	*g_scale_e_btn = NULL;
	static t_effect		f_n = GRAYSCALE;

	if (!g_scale_e_btn)
	{
		if (!(g_scale_e_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		g_scale_e_btn->name = "g_scale_e_btn";
		g_scale_e_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	g_scale_e_btn->visible = env->active_tab == EFFECTS;
	g_scale_e_btn->font_size = 12;
	g_scale_e_btn->anchor = &sgl_find_control(env->win, "effects_p")->align;
	g_scale_e_btn->align = (SDL_Rect){95, 4, 55, 16};
	g_scale_e_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->flags.effect == f_n)
		g_scale_e_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	g_scale_e_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	g_scale_e_btn->fore_color = 0x323335;
	env->flags.effect == f_n ? g_scale_e_btn->fore_color = 0x990000 : 0;
	g_scale_e_btn->click_callback = ctrl_effect_click;
	g_scale_e_btn->callback_data = env;
	ft_strcpy(g_scale_e_btn->text, "GrayScale");
	ft_memcpy(g_scale_e_btn->tag, &f_n, sizeof(t_effect));
}

void	init_comic_effect_button(t_env *env)
{
	static t_control	*comic_e_btn = NULL;
	static t_effect		f_n = COMIC;

	if (!comic_e_btn)
	{
		if (!(comic_e_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		comic_e_btn->name = "comic_e_btn";
		comic_e_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	comic_e_btn->visible = env->active_tab == EFFECTS;
	comic_e_btn->font_size = 12;
	comic_e_btn->anchor = &sgl_find_control(env->win, "effects_p")->align;
	comic_e_btn->align = (SDL_Rect){153, 4, 40, 16};
	comic_e_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->flags.effect == f_n)
		comic_e_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	comic_e_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	comic_e_btn->fore_color = 0x323335;
	env->flags.effect == f_n ? comic_e_btn->fore_color = 0x990000 : 0;
	comic_e_btn->click_callback = ctrl_effect_click;
	comic_e_btn->callback_data = env;
	ft_strcpy(comic_e_btn->text, "Comic");
	ft_memcpy(comic_e_btn->tag, &f_n, sizeof(t_effect));
}
