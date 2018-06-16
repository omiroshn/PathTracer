/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:43:42 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/11 19:08:04 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				malloc_fig(t_dlist *rows, t_fig *fig)
{
	t_dlist	*row;

	row = rows;
	while ((row = row->next) != rows)
		if (!ft_strncmp(row->content, "v ", 2))
			fig->v_c++;
		else if (!ft_strncmp(row->content, "vn ", 3))
			fig->vn_c++;
		else if (!ft_strncmp(row->content, "vt ", 3))
			fig->vt_c++;
	fig->v = ft_memalloc(sizeof(cl_float3) * (fig->v_c + 1));
	fig->vt = ft_memalloc(sizeof(cl_float3) * (fig->vt_c + 1));
	fig->vn = ft_memalloc(sizeof(cl_float3) * (fig->vn_c + 1));
}

int					count_materials(t_dlist *rows)
{
	t_dlist		*row;
	int			count;

	row = rows;
	count = 0;
	while ((row = row->next) != rows)
		if (!ft_strncmp(row->content, "newmtl ", 7))
			count++;
	return (count);
}

uint				add_texture(t_dlist **tex_l, char *source)
{
	t_texture	*tex;
	SDL_Surface	*tmp;
	t_dlist		*row;
	uint		i;

	row = *tex_l;
	i = 0;
	while (row && (row = row->next) != *tex_l && ++i)
		if (((t_texture *)row->content)->source
			&& !ft_strcmp(source, ((t_texture *)row->content)->source))
			return (i);
	tex = ft_memalloc(sizeof(t_texture));
	if (!(tmp = sgl_imgload(source)))
		ERR("Unknown texture file");
	tex->pixels = malloc(4 * tmp->w * tmp->h);
	ft_memcpy(tex->pixels, tmp->pixels, 4 * tmp->w * tmp->h);
	tex->w = tmp->w;
	tex->h = tmp->h;
	tex->source = ft_strdup(source);
	SDL_FreeSurface(tmp);
	ft_dlstpush_back(tex_l, ft_dlstnew(tex, sizeof(t_texture)));
	return (ft_dlstsize(*tex_l));
}

void				parse_mtl(t_mtl_material *materials,
								t_dlist *rows, t_env *env)
{
	char	**splitted;
	t_dlist	*row;
	int		i;

	row = rows;
	i = -1;
	while ((row = row->next) != rows)
		if (!ft_strncmp(row->content, "newmtl ", 7))
		{
			splitted = ft_strsplit(row->content, ' ');
			if (count_splitted(splitted) != 2)
				ERR("Invalid material in mtl file");
			materials[++i].name = ft_strdup(splitted[1]);
			free_splitted(splitted);
		}
		else if (i >= 0 && !ft_strncmp(row->content, "Kd ", 3))
			materials[i].color = parse_float3(row->content);
		else if (i >= 0 && !ft_strncmp(row->content, "map_Kd ", 7))
		{
			splitted = ft_strsplit(row->content, ' ');
			if (count_splitted(splitted) != 2)
				ERR("Invalid material source in mtl file");
			materials[i].tex_id = add_texture(&env->scene.tex_l, splitted[1]);
			free_splitted(splitted);
		}
}

t_mtl_material		*get_materials(char *string, t_env *env,
									char *mat_folder_name)
{
	char			**splitted;
	int				fd;
	t_dlist			*rows;
	t_mtl_material	*materials;
	char			*full_pass;

	splitted = ft_strsplit(string, ' ');
	if (count_splitted(splitted) != 2)
		ERR("Invalid mtllib property");
	full_pass = ft_strjoin(mat_folder_name, splitted[1]);
	if ((fd = open(full_pass, O_RDONLY)) == -1)
		ERR("Object mtl file doesn't exit");
	free(full_pass);
	free_splitted(splitted);
	rows = get_content(fd);
	materials = (t_mtl_material *)ft_memalloc(sizeof(t_mtl_material)
									* (count_materials(rows) + 1));
	parse_mtl(materials, rows, env);
	ft_dlstclear(&rows);
	return (materials);
}
