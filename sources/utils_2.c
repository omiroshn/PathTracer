/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 20:32:42 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/08 14:53:32 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	dir_vector(t_point dir, t_env *env)
{
	return (tofloat3(sgl_rotate_point(dir,
		(t_rotate){env->cam->rot.x, env->cam->rot.y, env->cam->rot.z})));
}

void		screenshot(t_env *env)
{
	char	name[128];
	char	*str;
	long	len;
	int		it;
	int		fd;

	sprintf(name, "screenshot_%ld.ppm", time(NULL));
	str = malloc(12 * env->win->w * env->win->h + 128);
	if ((fd = open(name, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR)) != -1)
	{
		len = sprintf(str, "P3\n%d %d\n%d\n", env->win->w, env->win->h, 255);
		it = -1;
		while (++it < env->win->w * env->win->h)
			len += sprintf(str + len, "%d %d %d ",
				((uint *)env->win->surf->pixels)[it] >> 16 & 0xFF,
				((uint *)env->win->surf->pixels)[it] >> 8 & 0xFF,
				((uint *)env->win->surf->pixels)[it] & 0xFF);
		write(fd, str, len);
		ft_printf("{green}Screenshot successfully saved to '%s'{nc}\n", name);
	}
	free(str);
}

inline int	count_splitted(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

inline void	free_splitted(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void		allocate_textures(t_env *env)
{
	t_texture	*tmp;
	t_dlist		*tex;
	uint		bts;
	uint		i;

	env->scene.texs_c = ft_dlstsize(env->scene.tex_l);
	env->scene.texs_info_h = ft_memalloc(env->scene.texs_c * sizeof(cl_int2));
	env->scene.texs_bts = 0;
	tex = env->scene.tex_l;
	while (tex && (tex = tex->next) != env->scene.tex_l
		&& (tmp = (t_texture *)tex->content))
		env->scene.texs_bts += tmp->w * tmp->h * 4;
	env->scene.all_texs = ft_memalloc(env->scene.texs_bts);
	bts = 0;
	i = 0;
	while (tex && (tex = tex->next) != env->scene.tex_l
		&& (tmp = (t_texture *)tex->content))
	{
		env->scene.texs_info_h[i++] = (cl_int2){.x = tmp->w, .y = tmp->h};
		ft_memcpy(env->scene.all_texs + bts, tmp->pixels, tmp->w * tmp->h * 4);
		bts += tmp->w * tmp->h;
		free(tmp->pixels);
	}
}
