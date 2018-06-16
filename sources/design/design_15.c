/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_15.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 19:52:47 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/01 21:20:12 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ctrl_pos_tab_click(t_env *env, t_control *c)
{
	env->sel_obj.active_pos = *(t_f_pos_tab *)c->tag;
	init_controls(env);
}

void	init_first_pos_button(t_env *env)
{
	static t_control	*first_pos_btn = NULL;
	static t_f_pos_tab	f_n = CENTER1;

	if (!first_pos_btn)
	{
		if (!(first_pos_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		first_pos_btn->name = "first_pos_btn";
		first_pos_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	first_pos_btn->visible = env->flags.obj_info;
	first_pos_btn->font_size = 12;
	first_pos_btn->anchor = &env->sel_obj.pos;
	first_pos_btn->align = (SDL_Rect){141, 65, 15, 15};
	first_pos_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->sel_obj.active_pos == f_n)
		first_pos_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	first_pos_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	first_pos_btn->fore_color = 0x323335;
	env->sel_obj.active_pos == f_n ? first_pos_btn->fore_color = 0x990000 : 0;
	first_pos_btn->click_callback = ctrl_pos_tab_click;
	first_pos_btn->callback_data = env;
	ft_strcpy(first_pos_btn->text, "1");
	ft_memcpy(first_pos_btn->tag, &f_n, sizeof(t_f_pos_tab));
}

void	init_second_pos_button(t_env *env)
{
	static t_control	*second_pos_btn = NULL;
	static t_f_pos_tab	f_n = CENTER2;

	if (!second_pos_btn)
	{
		if (!(second_pos_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		second_pos_btn->name = "second_pos_btn";
		second_pos_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	second_pos_btn->visible = env->flags.obj_info;
	second_pos_btn->font_size = 12;
	second_pos_btn->anchor = &env->sel_obj.pos;
	second_pos_btn->align = (SDL_Rect){158, 65, 15, 15};
	second_pos_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->sel_obj.active_pos == f_n)
		second_pos_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	second_pos_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	second_pos_btn->fore_color = 0x323335;
	env->sel_obj.active_pos == f_n ? second_pos_btn->fore_color = 0x990000 : 0;
	second_pos_btn->click_callback = ctrl_pos_tab_click;
	second_pos_btn->callback_data = env;
	ft_strcpy(second_pos_btn->text, "2");
	ft_memcpy(second_pos_btn->tag, &f_n, sizeof(t_f_pos_tab));
}

void	init_third_pos_button(t_env *env)
{
	static t_control	*third_pos_btn = NULL;
	static t_f_pos_tab	f_n = CENTER3;

	if (!third_pos_btn)
	{
		if (!(third_pos_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		third_pos_btn->name = "third_pos_btn";
		third_pos_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	third_pos_btn->visible = env->flags.obj_info;
	third_pos_btn->font_size = 12;
	third_pos_btn->anchor = &env->sel_obj.pos;
	third_pos_btn->align = (SDL_Rect){175, 65, 15, 15};
	third_pos_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	if (env->sel_obj.active_pos == f_n)
		third_pos_btn->border_color = (SDL_Color){0x99, 0, 0, 0xff};
	third_pos_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	third_pos_btn->fore_color = 0x323335;
	env->sel_obj.active_pos == f_n ? third_pos_btn->fore_color = 0x990000 : 0;
	third_pos_btn->click_callback = ctrl_pos_tab_click;
	third_pos_btn->callback_data = env;
	ft_strcpy(third_pos_btn->text, "3");
	ft_memcpy(third_pos_btn->tag, &f_n, sizeof(t_f_pos_tab));
}
