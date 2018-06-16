/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:56:17 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 12:12:10 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_load_msg(t_env *env, const char *msg, SDL_Renderer *rend)
{
	char		pg_str[32];
	SDL_Rect	pb;
	uint		offset;

	offset = env->win->h / 2;
	sgl_draw_str_center("Loading...", &(t_font){"PasseroOne", 56, 0x62BFED, 0},
		(SDL_Rect){0, offset - 140, env->win->w, 0}, rend);
	sgl_draw_str_center("Please, wait a little bit",
		&(t_font){"PasseroOne", 48, 0x3590F3, 0},
		(SDL_Rect){0, offset - 80, env->win->w, 0}, rend);
	pb = (SDL_Rect){env->win->w / 2 - 100, offset + 30, 200, 20};
	SDL_SetRenderDrawColor(rend, 194, 187, 240, 255);
	SDL_RenderDrawRect(rend, &pb);
	sprintf(pg_str, "%.0f %%", RANGE(ceil(env->load_progress * 100), 0, 100));
	pb = (SDL_Rect){pb.x + 1, pb.y + 1,
		RANGE(pb.w * env->load_progress, 0, pb.w) - 2, 18};
	sgl_draw_str_center(pg_str, &(t_font){"PasseroOne", 24, 0xFFFFFF, 0},
		(SDL_Rect){0, offset + 55, env->win->w, 0}, rend);
	SDL_SetRenderDrawColor(rend, 241, 227, 243, 255);
	SDL_RenderFillRect(rend, &pb);
	sgl_draw_str_center(msg, &(t_font){"SourceSans", 21, 0xFFFFFF, 0},
		(SDL_Rect){0, offset + 140, env->win->w, 0}, rend);
}

void	process_scene(int ac, char *scene_name, t_env *env)
{
	char					msg[256];
	t_parser_thread_info	info;

	ac != 2 ? display_usage(0) : 0;
	!ft_strcmp("-help", scene_name) ? display_usage(1) : 0;
	info.file_name = scene_name;
	info.env = env;
	pthread_create(&info.thread, 0, (void *(*)(void *))read_scene, &info);
	sprintf(msg, "Loading scene: '%s'", scene_name);
	while (env->flags.scene_parsed == 0)
	{
		SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 255);
		SDL_RenderClear(env->win->rend);
		draw_load_msg(env, msg, env->win->rend);
		if (poll_events(env) == 0)
			exit(sgl_quit(0, 0));
		SDL_RenderPresent(env->win->rend);
	}
}

void	process_kernels(t_env *env)
{
	pthread_t	thread;
	uint		delay;

	delay = 100;
	pthread_create(&thread, 0, (void *(*)(void *))parse_all_kernels, env);
	while (env->flags.kernels_parsed == 0 || delay-- > 0)
	{
		SDL_SetRenderDrawColor(env->win->rend, 0, 0, 0, 255);
		SDL_RenderClear(env->win->rend);
		env->flags.kernels_parsed == 0
			? draw_load_msg(env, "Parsing OpenCL kernels!", env->win->rend)
			: draw_load_msg(env, "Everything successfully loaded! Enjoy",
				env->win->rend);
		if (poll_events(env) == 0)
			exit(sgl_quit(0, 0));
		SDL_RenderPresent(env->win->rend);
	}
}
