/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_9.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 19:33:16 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 14:24:21 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ctrl_scroll(t_env *env, t_control *c, int y)
{
	float	v;
	float	*tg1;
	float	*tg2;

	v = *(float *)c->tag * (y > 0 ? 1.0F : -1.0F);
	tg1 = *(float **)(c->tag + sizeof(float));
	tg2 = *(float **)(c->tag + sizeof(float) + sizeof(void *));
	*tg1 += v;
	*tg2 += v;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_controls(env);
	init_scene(env);
}

void		init_glass_material_button(t_env *env)
{
	static t_control	*glass_m_btn = NULL;
	static t_material	f_n = GLASS;

	if (!glass_m_btn)
	{
		if (!(glass_m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		glass_m_btn->name = "glass_m_btn";
		glass_m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	glass_m_btn->font_size = 12;
	glass_m_btn->anchor = &env->sel_obj.pos;
	glass_m_btn->align = (SDL_Rect){96, 189, 20, 20};
	glass_m_btn->visible = env->flags.obj_info;
	glass_m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	glass_m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	glass_m_btn->fore_color = 0x323335;
	glass_m_btn->click_callback = ctrl_material_click;
	glass_m_btn->callback_data = env;
	ft_strcpy(glass_m_btn->text, "G");
	ft_memcpy(glass_m_btn->tag, &f_n, sizeof(t_material));
}

void		init_negative_material_button(t_env *env)
{
	static t_control	*negative_m_btn = NULL;
	static t_material	f_n = NEGATIVE_FIG;

	if (!negative_m_btn)
	{
		if (!(negative_m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		negative_m_btn->name = "negative_m_btn";
		negative_m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	negative_m_btn->font_size = 12;
	negative_m_btn->anchor = &env->sel_obj.pos;
	negative_m_btn->align = (SDL_Rect){118, 189, 20, 20};
	negative_m_btn->visible = env->flags.obj_info;
	negative_m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	negative_m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	negative_m_btn->fore_color = 0x323335;
	negative_m_btn->click_callback = ctrl_material_click;
	negative_m_btn->callback_data = env;
	ft_strcpy(negative_m_btn->text, "N");
	ft_memcpy(negative_m_btn->tag, &f_n, sizeof(t_material));
}

void		init_actions_panel(t_env *env)
{
	static t_control	*actions_p = NULL;

	if (!actions_p)
	{
		if (!(actions_p = sgl_new_control(LABEL, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		actions_p->name = "actions_p";
	}
	actions_p->border_size = 2;
	actions_p->align = (SDL_Rect){148, 0, 277, 24};
}

void		init_effects_panel(t_env *env)
{
	static t_control	*additional_p = NULL;

	if (!additional_p)
	{
		if (!(additional_p = sgl_new_control(LABEL, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		additional_p->name = "effects_p";
	}
	additional_p->visible = env->active_tab == EFFECTS;
	additional_p->border_size = 2;
	additional_p->align = (SDL_Rect){148, 22, 424, 24};
}
