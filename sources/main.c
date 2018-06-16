/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:43:02 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 11:59:52 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int ac, char **av)
{
	t_env	env;

	sgl_init();
	init_env(&env);
	process_scene(ac, av[1], &env);
	process_kernels(&env);
	init_controls(&env);
	init_scene(&env);
	while (true)
	{
		!env.flags.pause ? render_scene(&env) : 0;
		!env.flags.pause && env.flags.effect ? apply_effect(&env) : 0;
		if (poll_events(&env) == 0)
			return (sgl_quit(0, 0));
		SDL_UpdateTexture(env.win->tex, NULL, env.win->surf->pixels, 1);
		SDL_RenderCopy(env.win->rend, env.win->tex, NULL, NULL);
		env.flags.obj_info ? draw_info(&env.sel_obj.pos, &env) : 0;
		display_stats(&env, env.win->rend);
		sgl_draw_controls(env.win);
		SDL_RenderPresent(env.win->rend);
		handle_movement(&env);
	}
	return (sgl_quit(0, 0));
}
